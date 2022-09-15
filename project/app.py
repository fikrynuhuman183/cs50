
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from datetime import date
from flask import flash
from werkzeug.security import check_password_hash, generate_password_hash
from helpers import apology, login_required

#initialize flask
app = Flask(__name__)

#ensure templates are loaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# initialize the database
db = SQL("sqlite:///classes.db")

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/")
@login_required
def index():
    if session["acc_type"] == "teacher":
        return redirect("/teacher")
    else:
            return redirect("/student")

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # forget any users

    session.clear()

    # User reached route through POST
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # determine whether user is a teacher or student
        u_type = request.form.get("acc_type")

        #if the user is a student
        if u_type == "stdnt":
            # Query database for username
            rows = db.execute("SELECT * FROM students WHERE username = ?", request.form.get("username"))

            # Ensure username exists and password is correct
            if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
                return apology("invalid username and/or password", 403)

            # Remember which user has logged in
            session["user_id"] = rows[0]["std_id"]
            session["acc_type"] = u_type

            # Redirect user to home page
            return redirect("/student")

        #if the user is a teacher
        if u_type == "teacher":
            # Query database for username
            rows = db.execute("SELECT * FROM teachers WHERE username = ?", request.form.get("username"))

            # Ensure username exists and password is correct
            if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
                return apology("invalid username and/or password", 403)

            # Remember which user has logged in
            session["user_id"] = rows[0]["t_id"]
            session["acc_type"] = u_type

            # Redirect user to home page
            return redirect("/teacher")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")

@app.route("/register", methods=["GET","POST"])
def register():
    if request.method == "POST" :
        #extract the required data from the form
        name = request.form.get("username")
        password = request.form.get("password")
        u_type = request.form.get("acc_type")
        pass_hash = generate_password_hash(password)
        confirm = request.form.get("confirmation")

        conf_hash = generate_password_hash(confirm)
        #validate the login details
        if not name or password != confirm or not password:
            return apology("invalid username and/or password")

        #if user is a student
        if u_type == "stdnt":
            names = db.execute("SELECT username FROM students")
            for i in range(0, len(names)):
                if name == names[i]["username"]:
                    return apology("Student already exists, Please login")

            #Update the database
            db.execute("INSERT INTO students (username, hash) VALUES(?, ?)", name, pass_hash )
            #Auto login student after registration
            rows = db.execute("SELECT * FROM students WHERE username = ?", request.form.get("username"))
            session["user_id"] = rows[0]["std_id"]
            session["acc_type"] = u_type

            flash("Registration Successful! Please Add a subject to begin learning")

            return redirect("/student")
        #if user is a teacher
        else:
            names = db.execute("SELECT username FROM teachers")
            #check if the teacher is already registered
            for i in range(0, len(names)):
                if name == names[i]["username"]:
                    return apology("Teacher already exists, Please login")

            #if a teacher is registering ensure that they choose a subject
            sub_id = request.form.get("subject")

            #check for code
            code = request.form.get("code")
            if code != "1234":
                return apology("Invalid code, Please contact admin for more info")

            if not sub_id:
                return apology("Please select a subject you would like to teach")

            #Update the database
            db.execute("INSERT INTO teachers (username, hash, sub_id) VALUES(?, ?, ?)", name, pass_hash, sub_id)

            #Auto login teacher after registration
            rows = db.execute("SELECT * FROM teachers WHERE username = ?", request.form.get("username"))
            session["user_id"] = rows[0]["t_id"]
            session["acc_type"] = u_type
            flash("Registration Successful!")
            return redirect("/teacher")

    if request.method == "GET":
        subjects = db.execute("SELECT name, sub_id FROM subjects WHERE NOT sub_id IN (SELECT sub_id FROM teachers)")
        return render_template("register.html", subjects=subjects)

#the students homepage
@app.route("/student", methods=["GET","POST"])
@login_required
def studenthm():
    #prevent teachers from accessing this page
    if session["acc_type"] == "teachers":
        return apology("This page is for students only")

    if request.method == "POST":
        #remove subject
        subject = request.form.get("subject")
        db.execute("DELETE FROM link WHERE sub_id=(SELECT sub_id FROM subjects WHERE name=?) AND std_id=?", subject, session["user_id"])
        flash("Subject Removed")
        return redirect("/student")

    else:
        #query the required data
        sub_links = db.execute("SELECT subjects.name AS name, teachers.username AS username, teachers.link AS link FROM subjects JOIN teachers ON subjects.sub_id=teachers.sub_id WHERE teachers.sub_id IN (SELECT sub_id FROM link WHERE std_id =?)", session["user_id"])
        return render_template("student.html", sub_links=sub_links)

#adding a suject
@app.route("/addS", methods=["POST", "GET"])
@login_required
def addS():
        #prevent teachers from accessing this page
    if session["acc_type"] == "teachers":
        return apology("This page is for students only")

    if request.method == "POST":
        #obtain the required data from the form
        sub_id = request.form.get("subject")

        #check if the student is already registered
        stdid = db.execute("SELECT std_id FROM link WHERE sub_id=?", sub_id)

        #update the linking database
        db.execute("INSERT INTO link (sub_id, std_id) VALUES(?, ?)", sub_id, session["user_id"])
        flash("Subject added")
        return redirect("/student")

    else:
        #query the teachers and their respective subjects which student has not yet registered
        subjects = db.execute("SELECT name, sub_id FROM subjects WHERE NOT sub_id IN (SELECT sub_id FROM link WHERE std_id=?) AND sub_id IN (SELECT sub_id FROM teachers)", session["user_id"])

        return render_template("addS.html", subjects=subjects)

@app.route("/teacher", methods=["POST", "GET"])
@login_required

def teacher():
        #prevent students from accessing this page
    if session["acc_type"] == "stdnt":
        return apology("This page is for teachers only")

    if request.method == "POST":
        #update the link
        link = request.form.get("link")
        db.execute("UPDATE teachers SET link=? WHERE t_id=?", link, session["user_id"])
        return redirect("/teacher")

    if request.method == "GET":
        #query the required data
        students = db.execute("SELECT username FROM students WHERE std_id IN (SELECT std_id FROM link WHERE sub_id = (SELECT sub_id FROM teachers WHERE t_id = ?))", session["user_id"])
        return render_template("teacher.html", students=students)