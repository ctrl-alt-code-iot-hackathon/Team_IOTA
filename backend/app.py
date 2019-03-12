from flask import Flask, request
from firebase import firebase

db = firebase.FirebaseApplication('https://smart-button-iota.firebaseio.com/', None)

app = Flask(__name__)

@app.route('/update', methods=['GET'])
def index():
	if request.method=="GET":
		sid = request.args.get('id')
		text = request.args.get('text')
		status = request.args.get('status')
		db.put('switch' + sid, 'text', text)
		db.put('switch' + sid, 'status', status)
	return "Hello"

if __name__ == "__main__":
	app.run(debug=True)