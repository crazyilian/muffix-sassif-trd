
class Pt:
    def dot(self, other):
        return self.x * other.x + self.y * other.y

    def cross(self, other):
        return self.x * other.y - self.y * other.x

    @staticmethod
    def get_straight(self, other):
        a = self.y - other.y
        b = other.x - self.x
        c = self.cross(other)
        return a, b, c


class Straight:

    def __eq__(self, other):
        if self.b != 0 or other.b != 0:
            return self.a * other.b == other.a * self.b and self.c * other.b == other.c * self.b
        val1 = math.sqrt(self.a ** 2 + self.b ** 2)
        val2 = math.sqrt(other.a ** 2 + other.b ** 2)
        a1, c1 = self.a / val1, self.c / val1
        a2, c2 = other.a / val2, other.c / val2
        if (a1 < 0) != (a2 < 0):
            a1, a2, c1, c2 = a1, -a2, c1, -c2
        return a1 == a2 and c1 == c2

    def perpendicular(self, point: Pt):
        return Straight(-self.b, self.a, self.b * point.x - self.a * point.y)

    def get_value(self, point):
        return self.a * point.x + self.b * point.y + self.c

    def intersection(self, other):
        d = Pt(self.a, self.b).cross(Pt(other.a, other.b))
        dx = Pt(self.c, self.b).cross(Pt(other.c, other.b))
        dy = Pt(self.a, self.c).cross(Pt(other.a, other.c))
        return Pt(-dx / d, -dy / d)

    def dist_from_point(self, point):
        val = math.sqrt(self.a ** 2 + self.b ** 2)
        return abs(Straight(self.a / val, self.b / val, self.c / val).get_value(point))

    def parallel(self, dist):
        val = math.sqrt(self.a ** 2 + self.b ** 2)
        return Straight(self.a, self.b, self.c - dist * val)

    def is_parallel(self, other):
        return self.a * other.b == self.b * other.a

    def is_perpendicular(self, other):
        per = Straight(-self.b, self.a, 0)
        return per.a * other.b == per.b * other.a


class Triangle:
    def intersection_medians(self):
        return (self.A + self.B + self.C) / 3

    def intersection_altitudes(self):
        st1 = Straight(self.A, self.B).perpendicular(self.C)
        st2 = Straight(self.A, self.C).perpendicular(self.B)
        return st1.intersection(st2)

    def intersection_middle_pers(self):
        st1 = Straight(self.A, self.B).perpendicular((self.A + self.B) / 2)
        st2 = Straight(self.A, self.C).perpendicular((self.A + self.C) / 2)
        return st1.intersection(st2)


class Circle:
    def intersect_straight(self, st):
        pt = st.get_point()
        A = st.a ** 2 + st.b ** 2
        B = 2 * (-st.b * (pt.x - self.center.x) + st.a * (pt.y - self.center.y))
        C = (pt.x - self.center.x) ** 2 + (pt.y - self.center.y) ** 2 - self.radius ** 2
        D = B ** 2 - 4 * A * C
        if D < 0:
            return []
        D = math.sqrt(D)
        vector = Pt(-st.b, st.a)
        if D == 0:
            t = -B / (2 * A)
            return [pt + t * vector]
        t1 = (-B - D) / (2 * A)
        t2 = (-B + D) / (2 * A)
        return [pt + t1 * vector, pt + t2 * vector]

    def intersect_circle(self, other):
        x1, x2 = self.center.x, other.center.x
        y1, y2 = self.center.y, other.center.y
        a = -2 * (x1 - x2)
        b = -2 * (y1 - y2)
        c = (x1 ** 2 - x2 ** 2) + (y1 ** 2 - y2 ** 2) - (self.radius ** 2 - other.radius ** 2)
        return self.intersect_straight(Straight(a, b, c))

    def is_own(self, pt):
        return (pt.x - self.center.x) ** 2 + (pt.y - self.center.y) ** 2 == self.radius ** 2

    def tangent_pts(self, pt):
        if self.is_own(pt):
            return [pt]
        cir = Circle(pt, math.sqrt(abs(pt - self.center) ** 2 - self.radius ** 2))
        return self.intersect_circle(cir)

    def dist_by_circle(self, pt1, pt2):
        pt1 -= self.center
        pt2 -= self.center
        ang = (pt1.polar_angle() - pt2.polar_angle()) % (2 * math.pi)
        ang = min(ang, 2 * math.pi - ang)
        return self.radius * ang


