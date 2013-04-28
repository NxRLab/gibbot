

class MonkeyBot:
    def __init__(self, q1, q2, q1d=0, q2d=0):
        self.q1 = q1
        self.q2 = q2
        self.q1d = q1d
        self.q2d = q2d

    def advanceState(dt):
        self.q1 += self.q1d * dt
        self.q2 += self.q2d * dt

        # still need to update q1d and q2d in a physically realistic way...

    def __repr__(self):
        return '(q1={}, q2={}, q1d={}, q2d={})'.format(self.q1, self.q2, self.q1d, self.q2d)