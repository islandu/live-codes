#!/usr/bin/python3

from flask import Flask, Response, jsonify, request, g
from flask_httpauth import HTTPBasicAuth
import json
from notesdb import NotesRepository


api = Flask(__name__)
auth = HTTPBasicAuth()


@api.before_first_request
def startup():
    api.notesdb = NotesRepository('localhost:27017')


@auth.verify_password
def verify_password(username: str, password: str) -> bool:
    """"""
    try:
        user_id = api.notesdb.authenticate_user(username, password)
    except Exception as e:
        print(e)
        return False

    print(f"User '{username}' authenticated successfully")
    g.user_id = user_id    
    return True


@auth.error_handler
def unauthorized() -> Response:
    message = 'Unauthorized access'
    username = auth.username()
    
    if username:
        message = f"Authentication failed for user '{username}'"
    
    return json_response({'error': message}, 401)


@api.route('/api/notes', methods=['GET'])
@auth.login_required
def get_all_notes() -> Response:
    notes = api.notesdb.get_all_notes(g.user_id)
    return json_response(notes, 200)


@api.route('/api/notes/<note_id>', methods=['GET'])
@auth.login_required
def get_note(note_id: str) -> Response:
    note = api.notesdb.get_note(g.user_id, note_id)
    return json_response(note, 200)


@api.route('/api/notes', methods=['POST'])
@auth.login_required
def create_note() -> Response:
    request_body = json.loads(request.data)
    try:
        note_id = api.notesdb.create_note(g.user_id, request_body)
    except Exception as e:
        return json_response({'error': str(e)}, 400)
    
    return json_response({'id': note_id}, 200)


def json_response(body_obj, status_code: int) -> Response:
    response = jsonify(body_obj)
    response.status_code = status_code
    response.headers['Content-Type'] = 'application/json'
    return response


if __name__ == '__main__':
    api.run(host='0.0.0.0', port=5000)
