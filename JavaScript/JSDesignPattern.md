### JavaScript design pattern

> Object Oriented Programming

### CH1

* Store vars in object.
* For copy requirement, design function which returns object that store vars.
* And you also need new to initialize the object

#
    var CheckObject = function(){
      this.checkName = function(){
        //checkName
      }
      this.checkEmail = function(){
        //checkEmail
      }
    }
    
    var a = new CheckObject();
    a.checkEmail();

* However, everytime you create a new object, you need to copy the properties of "this" which is wasteful. So we need to use prototype here.

#
    var CheckObject = function(){};
    CheckObject.prototype = {
      checkName : function(){
        //checkName
      },
      checkEmail : function(){
        //checkEmail
      }
    }
       
    var a = new CheckObject();
    a.checkEmail();
    

