# Subclass circle

import shape

class Circle(shape.Shape):
    
    m_radius = int()

    def set_radius(self, radius):
        self.m_radius = radius
        return

    def get_radius(self):
        return self.m_radius

    def __init__(self, area, radius):
        super().__init__(area)
        self.set_radius(radius)
        return
