### Question1
```
(defun triangular-number (N) (if (= N 1) 1 (+ N (triangular-number (- N 1)))))

(triangular-number 5)

(triangular-number 6)
```

### Question2  
b. should there be two threads which attempt to run transfer(a, b) and transfer(b, a) at the same time, then a deadlock is going to occur because they try to acquire the resources in reverse order.   

* Exp: The thread sync priority is from -> to, and release in to->from which will cause a deadlock.  

### Question3  
d. After thread A is notified, or after two seconds.  

* Exp: https://www.baeldung.com/java-wait-notify  

### Qiestion 4
```
(defun recursive-list-length (L) (if (eq (cdr L) nil) 1 (+ 1 (recursive-list-length (cdr l)))))


(recursive-list-length '(1 2 3 5 7 11 13 17 19))
```
* Ref:https://stackoverflow.com/questions/19284998/implementing-length-recursively-for-arbitrary-sequences-not-just-lists

### Question 5
```
(defun ismember (atm lis) (cond ( (null lis) '() ) ((eql atm (car lis))) (t (ismember atm (cdr lis)))))

(ismember 'a '(1 2 3))
(ismember '1 '(1 2 3))
```
* Ref: http://web.eecs.utk.edu/~mberry/cs365s05/hwk/lisp/ismember.txt

### Question 6
```
aunt(X, Y) :-

	sister(X, Z),

	parent(Z, Y).
```
* X-aunt, Y-kid, Z-parent
* aunt(aunt, kid) :-
*   sister(aunt, parent)
*   parent(parent, kid)

### Question 7
```
sibling(X, Y) :
	parent(Z, X),
	parent(Z, Y).
```
* X,Y, Z-parent

### Question 8
c. 
```
class Thread1 implements Runnable {
  public void run() {}}
```
* Exp:
```
class MyClass implements Runnable {
    @Override
    public void run() {
        for(int i = 0; i < 10; i++){
            System.out.println(Thread.currentThread().getId() + " value " + i);
        }
        try {
            Thread.sleep(1000);
        }catch (InterruptedException e){
            e.printStackTrace();
        }
    }
}

public class ThreadLearning {
    public static void main(String[] args) {
        Thread t1 = new Thread(new MyClass());
        Thread t2 = new Thread(new MyClass());
        t1.start();
        t2.start();
    }
}
```

### Question 9
b.
```
Thread t = new Thread(X); t.start();
```

* Exp:

```
class MyClass implements Runnable {
    public static void main(String[] args) {
        Thread t1 = new Thread(new MyClass());
        Thread t2 = new Thread(new MyClass());
        t1.start();
        t2.start();
    }

    public void run() {
        for(int i = 0; i < 10; i++){
            System.out.println(Thread.currentThread().getId() + " value " + i);
        }
    }
}
```

### Question10
b,c,d. Two concurrent threads cannot access both balance and amt
* Exp: 
```
synchronized(objectidentifier) {
   // Access shared variables and other shared resources
}
```
