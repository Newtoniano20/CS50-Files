import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
import datetime

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
    cash = db.execute('SELECT cash FROM users WHERE id=?', session["user_id"])
    current_stocks = db.execute('SELECT * FROM stocks WHERE user_id = ?', session["user_id"])
    n = 0
    total_value = 0
    for cstock in current_stocks:
        print(lookup(cstock['symbol']))
        price = lookup(cstock['symbol'])['price']
        total_value += price*cstock['amount']
        current_stocks[n] = {
            'name': cstock['name'],
            'price': usd(price),
            'value': usd(price*cstock['amount']),
            'amount': cstock['amount']
        }
        n += 1
    return render_template('home.html', stocks=current_stocks, cash=cash, total_value=total_value)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template('buy.html', bought="")
    else:
        stock = lookup(request.form.get("symbol"))
        symbol = request.form.get("symbol")
        try:
            amount = int(request.form.get("shares"))
        except:
            return apology('Amount must be an integer')

        if amount <= 0:
            return apology('Amount must be greater than 0')

        if stock == None:
            return apology('Stock Symbol does not exist')
        else:
            cash = db.execute('SELECT cash FROM users WHERE id=?', session["user_id"])
            current_stocks = db.execute('SELECT * FROM stocks WHERE user_id = ?', session["user_id"])
            print(cash)
            if cash[0]['cash'] < amount * stock['price']:
                return apology('Not enough money to buy stock')
            for cstock in current_stocks:
                if cstock['name'] == stock['name']:
                    db.execute('UPDATE stocks SET amount=? WHERE user_id=? AND name=?',
                               amount+cstock['amount'] , session["user_id"], stock['name'])
                    db.execute('UPDATE users SET cash=? WHERE id=?', usd(cash[0]['cash']-amount*stock['price']), session["user_id"])
                    db.execute('INSERT INTO history (name, user_id, amount, symbol, time) VALUES (?, ?, ?, ?, ?)',
                               stock['name'], session["user_id"], amount, request.form.get("symbol"), datetime.datetime.now())
                    return redirect('/')
            db.execute('INSERT INTO stocks (name, user_id, amount, symbol) VALUES (?, ?, ?, ?)',
                       stock['name'], session["user_id"], amount, request.form.get("symbol"))
            db.execute('UPDATE users SET cash=? WHERE id=?', usd(cash[0]['cash']-amount*stock['price']), session["user_id"])
            db.execute('INSERT INTO history (name, user_id, amount, symbol, time) VALUES (?, ?, ?, ?, ?)',
                       stock['name'], session["user_id"], amount, request.form.get("symbol"), datetime.datetime.now())
            return redirect('/')


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    everything = db.execute('SELECT * FROM history WHERE user_id=?', session['user_id'])
    return render_template('history.html', everything=everything)


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
    if request.method == "GET":
        return render_template('quote.html')
    else:
        stock = lookup(request.form.get("symbol"))
        if stock == None:
            return apology('Stock Symbol does not exist')
        else:
            return render_template('quote.html', name=stock['name'], price=usd(stock['price']), symbol=stock['symbol'])


@app.route("/register", methods=["GET", "POST"])
def register():

    # Forget any user_id
    session.clear()

    if request.method == "GET":
        return render_template('register.html')

    else:
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        if request.form.get("password") == request.form.get("confirmation"):
            current_users = db.execute('SELECT username FROM users')
            print(current_users)
            for user in current_users:
                if user['username'] == request.form.get("username"):
                    return apology('User already exists')
            db.execute('INSERT INTO users (username, hash) VALUES (?, ?)', request.form.get(
                "username"), generate_password_hash(request.form.get("password")))

        else:
            return apology('Passwords do not match')
        session['user_id'] = db.execute('SELECT id FROM users WHERE username LIKE ?', request.form.get("username"))[0]['id']
        return redirect('/')


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "GET":
        return render_template('sell.html')
    else:
        stock = lookup(request.form.get("symbol"))
        amount = int(request.form.get("amount"))
        if amount <= 0:
            return apology('Amount must be greater than 0')

        if stock == None:
            return apology('Stock Symbol does not exist')
        else:
            cash = db.execute('SELECT cash FROM users WHERE id=?', session["user_id"])
            current_stocks = db.execute('SELECT * FROM stocks WHERE user_id = ?', session["user_id"])
            for cstock in current_stocks:
                if cstock['name'] == stock['name']:
                    if cstock['amount'] < amount:
                        return apology('You do not own that many of that stock')
                    db.execute('UPDATE stocks SET amount=? WHERE user_id=?',cstock['amount']-amount, session["user_id"])
                    db.execute('UPDATE users SET cash=? WHERE id=?', usd(cash[0]['cash']+amount*stock['price']) , session["user_id"])
                    db.execute('INSERT INTO history (name, user_id, amount, symbol, time) VALUES (?, ?, ?, ?, ?)',
                               stock['name'], session["user_id"], -amount, request.form.get("symbol"), datetime.datetime.now())
                    return redirect('/')
            return apology('You do not own any of that stock')


@app.route("/changepass", methods=["GET", "POST"])
def changepass():

    if request.method == "GET":
        return render_template('cp.html')

    else:
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        hash = db.execute('SELECT hash FROM users WHERE id=?', session['user_id'])[0]['hash']
        if check_password_hash(hash, request.form.get("password")):
            db.execute('UPDATE users SET hash=? WHERE id=?', generate_password_hash(
                request.form.get("newpassword")), session['user_id'])
            return redirect('/')

        else:
            return apology('Incorrect Password')
