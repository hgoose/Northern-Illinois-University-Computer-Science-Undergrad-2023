import electronics
import computer
import phone
import smart_televison

# User Input for brand name, operating system, phone number

BrandNameElec = input("Enter an electronics brand name: ")

BrandNameComputer = input("\nEnter an electronics brand name: ")
OsComputer = input("Enter an operating system: ")

BrandNamePhone = input("\nEnter an electronics brand name: ")
OsPhone = input("Enter an operating system: ")
PhoneNumber = input("Enter a phone number: ")

BrandNameSmartTv = input("\nEnter an Electronics brand name: ")
OsTv = input("Enter an operating system: ")
sizeTv = input("Enter size of television: ")

# Instantiate objects 

electronicsObject = electronics.Electronics(BrandNameElec)
computerObject = computer.Computer(BrandNameComputer, OsComputer)
phoneObject = phone.Phone(BrandNamePhone, OsPhone, PhoneNumber)
tvObject = smart_televison.SmartTelevision(BrandNameSmartTv, OsTv, sizeTv)

# Output electronics object
print("\n\nThe Electronics Object: ", "\nBrand name: %s" % (electronicsObject.getBrandName()))

# Output computer object
print("\nThe Computer Object: ", "\nBrand Name: %s" % (computerObject.getBrandName()),
        "\nOperating Sytem: %s" % (computerObject.getOperatingSystem()))

# Ouput Phone object
print("\nThe Phone Object: ", "\nBrand Name: %s" % (phoneObject.getBrandName()),
        "\nOperating System: %s" % (phoneObject.getOperatingSystem()),
        "\nPhone Number: %s" % (phoneObject.getPhoneNumber()))

# Ouput Television object
print("\nThe SmartTv Object: ", "\nBrand Name: %s" % (tvObject.getBrandName()),
        "\nOperating System: %s" % (tvObject.getOperatingSystem()),
        "\nSize: %s" % (tvObject.getSize()))

