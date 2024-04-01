import computer

# DEFINE SUB - PHONE

class Phone(computer.Computer):

    m_phone_number = str()

    def __init__(self, brand_name, operating_system, phone_number):
        """ constructor """
        super().__init__(brand_name, operating_system)
        self.setPhoneNumber(phone_number)
        return

    def setPhoneNumber(self, phone_number):
        """ Set phone number """
        self.m_phone_number = phone_number
        return

    def getPhoneNumber(self):
        """ return phone number """
        return self.m_phone_number


