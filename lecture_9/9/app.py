from flask import Flask, render_template, request

app=Flask(__name__)

SPORTS=[
    "Cricket",
    "Football",
    "Volleyball"
]
REGISTRANTS={}

@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)

@app.route("/register", methods=["POST"])
def register():

    name = request.form.get("name")
    sport = request.form.get("sport")
    #validate registration
    if not name or sport not in SPORTS:
        return render_template("failed.html")
    REGISTRANTS[name] = sports

    #confirm registration
    return render_template("success.html")

@app.route("/regi", methods=["POST"])
def regi():
    return render_template("regi.html", REGISTRANTS=REGISTRANTS)