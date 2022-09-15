import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from datetime import date
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


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
    """Show portfolio of stocks"""
    #obtain required data from the database(bought)
    data_b = db.execute("SELECT com_symbol, SUM(num_share) AS numsha, SUM(total) AS total FROM transactions WHERE action=? AND buyer_id=? GROUP BY com_symbol", "Bought", session["user_id"])

    #obtain daata about sold share
    data_s = db.execute("SELECT com_symbol, SUM(num_share) AS numsha, SUM(total) AS total FROM transactions WHERE action=? AND buyer_id=? GROUP BY com_symbol", "Sold", session["user_id"])

    #query the remaining amount of cash
    cash = usd(db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"])

    #query the total value of available shares
    total = 0

    #include the name of company and calculate the total and format it
    for dat_b in data_b:
        com_details = lookup(dat_b["com_symbol"])
        dat_b["name"] = com_details["name"]
        for dat_s in data_s:
            if dat_s["com_symbol"] == dat_b["com_symbol"]:
                dat_b["total"] = float(dat_b["total"]) - float(dat_s["total"])
                dat_b["numsha"] = int(dat_b["numsha"]) - int(dat_s["numsha"])

        #update the total value
        total += dat_b["total"]
        dat_b["total"] = usd(dat_b["total"])

    #format total
    total = usd(total)
    #render the index.html
    return render_template("index.html", shares = data_b, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    #check for method
    if request.method == "POST":
        symbol = request.form.get("symbol")
        num_share = request.form.get("shares")

        #validate the user inputs
        if not symbol or lookup(symbol) == None:
            return apology("Invalid Symbol/Symbol does not exist")
        if not num_share or float(num_share) < 1:
            return apology("Please input a valid number of shares to buy")

        #obtain information about the user
        data = lookup(symbol)

        #obtain the price of a share
        price = data["price"]

        #obtain the cash of user
        cash = db.execute("SELECT cash FROM users WHERE id= ?", session["user_id"] )

        #calculate the total cost
        total_cost = price*int(num_share)

        #check if enough fund is present
        if float(cash[0]["cash"]) < total_cost:
            return apology("Not enough money to process the transaction")

        #Update the database
        db.execute("INSERT INTO transactions (buyer_id, com_symbol, unit_price, num_share, total, date, action) VALUES(?,?,?,?,?,?,?)", session["user_id"], symbol.upper(),price,num_share,total_cost,str(date.today()), "Bought")

        #calculate the remaining cash
        new_cash = float(cash[0]["cash"]) - total_cost

        #update the users database
        db.execute("UPDATE users SET cash=? WHERE id=?", str(new_cash), session["user_id"])

        return redirect("/")
    if request.method == "GET":
        return render_template("buy.html")



@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user = session["user_id"]
    #query the required data
    shares = db.execute("SELECT com_symbol, num_share, total, action FROM transactions WHERE buyer_id=?", user)

    #define a variable for storing total amount of cash
    total = 0

    #obtain the name of the company
    for share in shares:
        com_details = lookup(share["com_symbol"])
        share["name"] = com_details["name"]
        total += float(share["total"])
        share["total"] = usd(share["total"])

    total = usd((total))

    #render the index page
    return render_template("history.html", shares=shares, total=total)



@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

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


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        #validate symbol field
        if not symbol:
            return apology("Please input a symbol")

        #obtain the required data
        data = lookup(symbol)

        #validate the data
        if data != None:
            return render_template("quoted.html", name=data["name"], price=usd(data["price"]) )
        else:
            return apology("Invalid symbol")

    if request.method == "GET":
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST" :
        #extract the required data from the form
        name = request.form.get("username")
        password = request.form.get("password")
        pass_hash = generate_password_hash(password)
        confirm = request.form.get("confirmation")

        conf_hash = generate_password_hash(confirm)
        #validate the login details
        if not name  or password != confirm or not password:
            return apology("invalid username and/or password")

        names = db.execute("SELECT username FROM users")
        for i in range(0, len(names)):
            if name == names[i]["username"]:
                return apology("user already exists, Please login")

        #Update the database
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", name, pass_hash )
        return redirect("/login")

    if request.method == "GET":
        return  render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    data_b = db.execute("SELECT com_symbol, SUM(num_share) AS numsha FROM transactions WHERE action=? AND buyer_id=? GROUP BY com_symbol", "Bought", session["user_id"])

    #obtain daata about sold share
    data_s = db.execute("SELECT com_symbol, SUM(num_share) AS numsha FROM transactions WHERE action=? AND buyer_id=? GROUP BY com_symbol", "Sold", session["user_id"])

    #Calculate the total shares
    for dat_b in data_b:
        for dat_s in data_s:
            if dat_s["com_symbol"] == dat_b["com_symbol"]:
                dat_b["numsha"] = int(dat_b["numsha"]) - int(dat_s["numsha"])

    #check for method
    if request.method == "POST":
        symbol = request.form.get("symbol")
        num_share = request.form.get("shares")

        #validate the user inputs
        if not symbol or lookup(symbol) == None:
            return apology("Invalid Symbol/Symbol does not exist")
        if not num_share or float(num_share) < 1:
            return apology("Please input a valid number of shares to sell")


        data = lookup(symbol)
        for dat in data_b:
            if symbol == dat["com_symbol"]:
                if int(dat["numsha"]) < int(num_share):
                    return apology("Not enough shares at hand to sell")
        #obtain the price of a share
        price = data["price"]


        cash = db.execute("SELECT cash FROM users WHERE id= ?", session["user_id"] )

        #calculate the total cost
        total_cost = price*int(num_share)



        #Update the database
        db.execute("INSERT INTO transactions (buyer_id, com_symbol, unit_price, num_share, total, date, action) VALUES(?,?,?,?,?,?,?)", session["user_id"], symbol.upper(),price,num_share,total_cost,str(date.today()), "Sold")

        #calculate the remaining cash
        new_cash = float(cash[0]["cash"]) + total_cost

        #update the users database
        db.execute("UPDATE users SET cash=? WHERE id=?", str(new_cash), session["user_id"])

        return redirect("/")
    else:


        return render_template("sell.html", shares=data_b)
