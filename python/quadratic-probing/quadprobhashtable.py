#!/usr/bin/python3
import sys
from typing import Iterator
from siphashc import siphash
from sympy import isprime

class QuadProbHashTable:
    """Hash table that uses quadratic probing for hash collisions (computed with SipHash)"""
    def __init__(self, capacity: int, siphashkey: str):
        self._siphashkey = siphashkey
        capacity *= 2
        while not isprime(capacity):
            capacity += 1
        # make table size the next prime number after requested capacity times 2
        self._table = [[None, None]] * capacity
        self._count = 0 # number of keys in the table
    
    @property
    def load_factor(self) -> float:
        # We want this to be <= 0.5
        return self._count / len(self._table)
    
    def __setitem__(self, key: str, value: str) -> None:
        index = self._get_quadprob_index(key)
        
        if self._table[index][0] is not None:
            self._table[index][1] = value
        else:
            self._table[index] = [key, value]
            self._count += 1

        if self.load_factor >= 0.5:
            print(f"QuadProbHashTable: Hash-table load factor is {self.load_factor}; must resize", file=sys.stderr)
            self._rehash_table()
    
    def __getitem__(self, key: str) -> str:
        index = self._get_quadprob_index(key)
        k, v = self._table[index]
        if k is None:
            raise KeyError(key)
        return v

    def __iter__(self) -> Iterator[str]:
        for key, _ in filter(lambda x: x[0], self._table):
            yield key

    def __len__(self) -> int:
        return self._count

    def _rehash_table(self):
        new_capacity = len(self._table) * 2
        while not isprime(new_capacity):
            new_capacity += 1
        print(f"QuadProbHashTable: Resizing hash table from {len(self._table)} to {new_capacity} and rehashing", file=sys.stderr)
        old_table = self._table
        self._table = [[None, None]] * new_capacity
        for key, value in filter(lambda x: x[0], old_table):
            index = self._get_quadprob_index(key)
            self._table[index] = [key, value]

        del old_table

    def _get_table_index(self, key: str) -> int:
        index = siphash(self._siphashkey, key) % len(self._table)
        print(f"QuadProbHashTable: '{key}' hashed to index {index}", file=sys.stderr)
        return index
    
    def _get_quadprob_index(self, key: str) -> int:
        index = self._get_table_index(key)
        k = 1
        # until empty slot or existing key is found
        while self._table[index][0] is not None:
            if key == self._table[index][0]:
                break
            print(f"QuadProbHashTable: Hash collision for key '{key}' on index {index}", file=sys.stderr)
            index = (index + (k ** 2)) % len(self._table)
            k += 1

        print(f"QuadProbHashTable: Key '{key}' mapped to index {index}", file=sys.stderr)
        return index

if __name__ == '__main__':
    import string
    import random
    
    def random_ascii(n: int) -> str:
        return ''.join(random.choices(string.printable[:-6], k=n))
    
    siphashkey = random_ascii(16)
    hashtable = QuadProbHashTable(4, siphashkey)
    
    test_dict1 = {random_ascii(8): random_ascii(8) for _ in range(16)}
    test_dict2 = {k: random_ascii(8) for k in test_dict1}
    for k, v in test_dict1.items():
        hashtable[k] = v

    for k, v in test_dict1.items():
        assert(hashtable[k] == v)

    for k, v in test_dict2.items():
        hashtable[k] = v

    for k, v in test_dict2.items():
        assert(hashtable[k] == v)

    assert(len(hashtable) == len(test_dict1))
    print("All tests passed!")
