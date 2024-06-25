import matplotlib.pyplot as plt


class Point:
    def __init__(self, x: float, y: float):
        self.x = x
        self.y = y

    def __iadd__(self, other):
        self.x += other.x
        self.y += other.y

    def __isub__(self, other):
        self.x -= other.x
        self.y -= other.y

    def __imul__(self, other: float):
        self.x *= other
        self.y *= other

    def __itruediv__(self, other: float):
        self.x /= other
        self.y /= other

    def __add__(self, other):
        return Point(self.x + other.x, self.y + other.y)

    def __sub__(self, other):
        return Point(self.x - other.x, self.y - other.y)

    def __mul__(self, other: float):
        return Point(self.x * other, self.y * other)

    def __truediv__(self, other: float):
        return Point(self.x / other, self.y / other)

    def __str__(self):
        return f"({self.x}, {self.y})"

    def distance(self, other) -> float:
        return ((self.x - other.x)**2 + (self.y - other.y)**2)**0.5

    def draw(self, color="#000000"):
        plt.scatter(self.x, self.y, c=color)


class Vector:
    def __init__(self, x: float, y: float):
        self.x = x
        self.y = y

    def __add__(self, other):
        self.x += other.a.x
        self.y += other.b.x

    def __sub__(self, other):
        self.x -= other.a.x
        self.y -= other.b.x

    def size(self) -> float:
        return (self.x**2 + self.y**2)**0.5

    def normalize(self):
        return Vector(-self.y, self.x)

    def scalar_multiply(self, other) -> float:
        return self.x * other.x + self.y * other.y

    def vec_multiply(self, other) -> float:
        return self.x * other.y - self.y * other.x

    def draw(self, color="#AA0000"):
        plt.plot((0, self.x), (0, self.y), c=color)


class Line:
    def __init__(self, a: float, b: float, c: float):
        self.a = a
        self.b = b
        self.c = c

    def distance_from_point(self, other: Point) -> float:
        return abs(self.a * other.x + self.b * other.y + self.c) / (self.a**2 + self.b**2)**0.5

    def line_intersect(self, other) -> Point:
        temp = self.a * other.b - other.a * self.b
        return Point((self.b * other.c - other.b * self.c) / temp,
                     (other.a * self.c - self.a * other.c) / temp)


class Segment:
    def __init__(self, a: Point, b: Point):
        self.a = a
        self.b = b

    def size(self) -> float:
        return ((self.a.x - self.b.x)**2 + (self.a.y - self.b.y)**2)**0.5

    def is_intersect_segment(self, other) -> bool:
        angle1 = Vector(other.a.x - self.a.x, other.a.y - self.a.y).vec_multiply(
            Vector(self.b.x - self.a.x, self.b.y - self.a.y))
        angle2 = Vector(other.b.x - self.a.x, other.b.y - self.a.y).vec_multiply(
            Vector(self.b.x - self.a.x, self.b.y - self.a.y))
        if angle1 * angle2 > 0:
            return False
        angle1 = Vector(self.a.x - other.a.x, self.a.y - other.a.y).vec_multiply(
            Vector(other.b.x - other.a.x, other.b.y - other.a.y))
        angle2 = Vector(self.b.x - other.a.x, self.b.y - other.a.y).vec_multiply(
            Vector(other.b.x - other.a.x, other.b.y - other.a.y))
        if angle1 * angle2 > 0:
            return False
        return True
    
    def draw(self, color="#00AA00"):
        plt.plot((self.a.x, self.b.x), (self.a.y, self.b.y), c=color)


def seg_line_intersect(point: Point, seg: Segment) -> bool:  # is segment intersect line from (0, 0) to Point
    angle1 = point.x * seg.a.y - point.y * seg.a.x
    angle2 = point.x * seg.b.y - point.y * seg.b.x
    return angle1 * angle2 <= 0  # only for this task need '<', not '<='


def split_segment(seg: Segment, count: int = 10) -> list[Point]:  # points on segment
    return [Point((seg.a.x * (count - mult) + seg.b.x * mult) / count,
                  (seg.a.y * (count - mult) + seg.b.y * mult) / count) for mult in range(count + 1)]


def main():
    pass


if __name__() == "__main__":
    main()
    plt.show()
