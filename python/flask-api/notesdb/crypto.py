import binascii
import hashlib
import os


def generate_salt(byte_count: int) -> str:
    """Generate random salt with the specified number of bytes
    
    Parameters
    ----------
    byte_count : int
        Number of random bytes to generate
    
    Returns
    -------
    str
        Hex string of the random bytes
    """
    b_str = os.urandom(byte_count)
    return binascii.hexlify(b_str).decode('ascii')


def hash_password(password: str, salt: str) -> str:
    """Hashes password plaintext with SHA-256 and provided salt
    
    Parameters
    ----------
    password : str
        Password plaintext
    salt : str
        Random salt used for hashing
    
    Returns
    -------
    str
        Hex string of the SHA-256 hash
    """
    salted_password = binascii.unhexlify(salt) + bytes(password, encoding='utf8')
    hasher = hashlib.sha256()
    hasher.update(salted_password)
    return hasher.hexdigest()


def hash_matches(hash: str, password: str, salt: str) -> bool:
    """Checks if password matches the salted hash
    
    Parameters
    ----------
    hash : str
        Salted hash to compare against
    password : str
        Plaintext password to authenticate
    salt : str
        Salt used to create the original hash
    
    Returns
    -------
    bool
        True if authenticated, otherwise False
    """
    hashed_password = hash_password(password, salt)
    return hash == hashed_password
