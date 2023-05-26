# DEFINE SUPER

class Electronics:

    m_brand_name = str()
    

    def __init__(self, brand_name):
        self.setBrandName(brand_name)
        return

    def setBrandName(self, brand_name):
        self.m_brand_name = brand_name
        return

    def getBrandName(self):
        return self.m_brand_name












