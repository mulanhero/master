class BaseClass():
  def method1(self):
      print "base method1"
        
  def method2(self, name):    
      print "base method2:" + name
      
class DerivedClass(BaseClass):
  def method1(self):
        BaseClass.method1(self);
        print "DerivedClass method1" 
        
  def method2(self):
        print "DerivedClass method2"     
         
def main():           
  c = DerivedClass()
  c.method1()
  c.method2()

if __name__== "__main__":
  main()
