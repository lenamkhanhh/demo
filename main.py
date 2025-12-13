from math import isqrt as sq
from abc import ABC, abstractmethod

A = 16
print(sq(A))


class Vehicle(ABC):
    @abstractmethod
    def go():
        pass
    @abstractmethod
    def stop():
        pass
    
class Car(Vehicle):
    def __init__(self, name):
        self.name = name
    def go(self):
        print(f"This {self.name} is starting")
    def stop(self):
        print(f"This {self.name} has stopped")

car = Car("Ford")
# car.go()
# car.stop()


class A:
    def __init__(self, num):
        self.num = num
    def show(self):
        print(self.num)

class B(A): 
    def show(self):
        print(self.num + 1)
        
tmp = B(1)
# tmp.show()