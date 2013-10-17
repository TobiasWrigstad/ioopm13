package exceptions;
/**
 * @author Tobias Wrigstad (tobias.wrigstad@it.uu.se)
 * @date 2013-10-12
 */
import java.util.Set;
import java.util.HashSet;

public class ExceptionDemo {
    public static class ExceptionInA extends RuntimeException {}
    public static class ExceptionInB extends RuntimeException {}
    public static class ExceptionInC extends ExceptionInB {}
    public static class ExceptionInD extends RuntimeException {}

    public static Set<String> list = new HashSet<String>();

    public static int depth = 0;
    public static void enter(String s) {
	++depth; 
	for (int i=0; i<depth; ++i) System.out.print("    ");
	System.out.print(">");
	System.out.println(s);
    }
    public static void exit(String s) {
	--depth; 
	for (int i=0; i<depth; ++i) System.out.print("    ");
	System.out.print("<");
	System.out.println(s);
    }

    public void a(char stop) {
	enter("a"); 

	if (stop == 'a') throw new ExceptionInA();

	try {
	    b(stop); 
	} finally {
	    list.add("this code got run");
	}
	
	list.add("a exited normally");
	exit("a"); 
    }
    public void b(char stop) {
	enter("b"); 
	if (stop == 'b') throw new ExceptionInB();

	c(stop); 

	list.add("b exited normally");
	exit("b"); 
    }
    public void c(char stop) {
	enter("c"); 
	if (stop == 'c') throw new ExceptionInC();

	d(stop); 

	list.add("c exited normally");
	exit("c"); 
    }
    private static int dCalls = 0;
    public void d(char stop) {
	enter("d"); 
	if (stop == 'd') throw new ExceptionInD();

	if (dCalls++ > 3) return;

	d(stop); 

	list.add("d exited normally");
	exit("d"); 
    }

    public static void main(String args[]) {
	enter("main");
	char stop = 'e';

	if (args.length == 1) {
	    stop = args[0].charAt(0);
	} else {
	    System.out.println("Run this program with arguments a, b, c or d\n" + 
			       "to observe the behaviour of the program when\n" + 
			       "exceptions are being thrown.\nYou'll also have" + 
			       " to look at the code!\n\n");
	}

	ExceptionDemo ed = new ExceptionDemo();

	try {
	    ed.a(stop);
	} catch (ExceptionInA eia) {
	    System.out.println("Exception thrown in A");
	} catch (RuntimeException rte) {
	    System.out.println("Caught exception: " + rte.getClass().getName());
	}
	depth = 1;
	exit("main");

	System.out.println("Any output below is unordered:");
	for (String msg : list) System.out.println(msg);
    }
}
