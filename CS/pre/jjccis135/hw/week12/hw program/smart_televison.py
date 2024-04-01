import computer

class SmartTelevision(computer.Computer):

    m_size = str()
        
    def __init__(self, brand_name, operating_system, size):
        super().__init__(brand_name, operating_system)
        self.setSize(size)
        return  

    def setSize(self, size):
        self.m_size = size
        return

    def getSize(self):
        return self.m_size
        
