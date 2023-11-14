from datetime import datetime
from bson.objectid import ObjectId
from pymongo import MongoClient
from pymongo.collection import Collection
from .crypto import hash_matches


class NotesRepository:
    """"""
    def __init__(self, host: str, **kwargs):
        """"""
        try:
            self._client = MongoClient(host, **kwargs)
        except Exception as e:
            raise self._connect_failure(host) from e
    
    def close_connection(self) -> None:
        self._client.close()

    def authenticate_user(self, username: str, password: str) -> str:
        """"""
        api_user = self._users_collection.find_one({
            'username': username.lower()
        })
        
        if not api_user:
            raise self._auth_failure(username)
        
        password_hash = api_user['passwordHash']
        password_salt = api_user['passwordSalt']
        
        if not password_hash or not password_salt:
            raise self._auth_failure(username)
        
        if not hash_matches(password_hash, password, password_salt):
            raise self._auth_failure(username)
        
        return str(api_user['_id'])
    
    def get_note(self, user_id: str, note_id: str) -> dict:
        """"""
        note = self._notes_collection.find_one({
            'userId': ObjectId(user_id),
            '_id': ObjectId(note_id)
        })
        
        if not note:
            raise self._note_not_found(note_id)
        
        return self._sanitize_note(note)
    
    def get_all_notes(self, user_id: str) -> list[dict]:
        """"""
        notes = self._notes_collection.find({'userId': ObjectId(user_id)})
        return [self._sanitize_note(n) for n in notes]
        
    def create_note(self, user_id: str, note: dict) -> str:
        """"""
        if 'contents' not in note:
            raise KeyError("'contents' property required")
        
        now = datetime.now()
        now_str = now.strftime("%Y-%m-%dT%H:%M:%S.%f")[:-3] + "Z"
        note['userId'] = ObjectId(user_id)
        note['created'] = now_str
        note['modified'] = now_str
        
        insert_result = self._notes_collection.insert_one(note)
        return str(insert_result.inserted_id)
    
    @property
    def _users_collection(self) -> Collection:
        return self._get_collection('userdata', 'users')
    
    @property
    def _notes_collection(self) -> Collection:
        return self._get_collection('userdata', 'notes')
    
    def _get_collection(self, database: str, collection: str) -> Collection:
        try:
            db = self._client[database]
        except Exception as e:
            raise FileNotFoundError(f"'{database}' db not found") from e
        
        try:
            return db[collection]
        except Exception as e:
            raise FileNotFoundError(
                f"'{collection}' collection not found in db '{database}'"
            ) from e
    
    @staticmethod
    def _sanitize_note(note: dict) -> dict:
        def sanitizer():
            for k, v in note.items():
                if k == 'userId':
                    continue
                elif k == '_id':
                    yield 'id', str(v)
                else:
                    yield k, v
        
        return {k: v for k, v in sanitizer()}
    
    @staticmethod
    def _auth_failure(username: str) -> PermissionError:
        return PermissionError(
            f"Authentication failed for user '{username}'"
            if username
            else "Username required"
        )

    @staticmethod
    def _note_not_found(note_id: str) -> FileNotFoundError:
        return FileNotFoundError(
            f"Note with id '{note_id}' not found"
        )
    
    @staticmethod
    def _connect_failure(host: str) -> ConnectionError:
        return ConnectionError(
            f"Unable to connect to MongoDB instance at '{host}'"
        )
