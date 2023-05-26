# Superclass shape
 
class Shape:
    
    m_area = int()

    def set_area(self, area):
        self.m_area = area
        return

    def get_area(self):
        return self.m_area

    def __init__(self, area):
        self.set_area(area)
        return
