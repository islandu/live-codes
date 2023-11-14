import binascii
import hashlib
import os


def generate_salt(byte_count: int) -> str:
    b_str = os.urandom(byte_count)
    return binascii.hexlify(b_str).decode('ascii')


def hash_password(password: str, salt: str) -> str:
    salted_password = binascii.unhexlify(salt) + bytes(password, encoding='utf8')
    hasher = hashlib.sha256()
    hasher.update(salted_password)
    return hasher.hexdigest()


def hash_matches(hash: str, password: str, salt: str) -> bool:
    hashed_password = hash_password(password, salt)
    return hash == hashed_password
