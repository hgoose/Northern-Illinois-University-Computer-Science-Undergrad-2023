import electronics

class Computer(electronics.Electronics):
    
    m_operating_system = str()

    def __init__(self, brand_name, operating_system):
        """ Constructor """
        super().__init__(brand_name)
        self.setOperatingSystem(operating_system)
        return
    
    def setOperatingSystem(self, operating_system):
        """ set operating system """
        self.m_operating_system = operating_system
        return

    def getOperatingSystem(self):
        """ return operating system """
        return self.m_operating_system








