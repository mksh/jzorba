package io.github.mksh;

import java.lang.reflect.*;
import java.nio.file.Paths;
import junit.framework.Test;
import junit.framework.TestCase;
import junit.framework.TestSuite;
import junit.extensions.TestSetup;

import io.github.mksh.jzorba.JZorba;
import io.github.mksh.jzorba.JZorbaQuery;


/**
 * JZorba basic test suite.
 */
public class JZorbaTest 
    extends TestCase
{

    /**
     * Create the test case
     *
     * @param testName name of the test case
     */
    public JZorbaTest( String testName )
    {
        super( testName );
    }

    /**
     * @return the suite of tests being tested
     */
    public static Test suite()
    {
        return new TestSetup(new TestSuite(JZorbaTest.class)) {

            protected void setUp() throws Exception {
                String currentPath = Paths.get(".").toAbsolutePath().normalize().toString();
                String jZorbaLibPath = Paths.get(currentPath, "target/classes/libjzorba.so").normalize().toString();
                String debugS = String.format(
                    "Loading libjzorba.so, currentPath=%s, jZorbaLibPath=%s;",
                    currentPath,
                    jZorbaLibPath
                );
                JZorba.isDynLibLoaded = true;
                System.out.println(debugS);
                System.load(jZorbaLibPath);
            }
                
            protected void tearDown() throws Exception {
                JZorba.close();
            }   
        };

    }


    /**
     * JZorba test helpers
     */

    private long getJZorbaPrivatePointerField(JZorba jZorba, String fieldName) {
        try {
            Field privateField = JZorba.class.getDeclaredField(fieldName);
            privateField.setAccessible(true);
            Long value = (Long) privateField.get(jZorba);
            System.out.println(String.format("value of %s is %s", fieldName, value.toString()));
            return (long) value;
        } catch (IllegalAccessException|NoSuchFieldException e)  {
            return 0;
        }
        
    }

    private long getJZorbaQueryPrivatePointerField(JZorba jZorba, String fieldName) {
        try {
            Field privateField = JZorba.class.getDeclaredField(fieldName);
            privateField.setAccessible(true);
            Long value = (Long) privateField.get(jZorba);
            System.out.println(String.format("value of %s is %s", fieldName, value.toString()));
            return (long) value;
        } catch (IllegalAccessException|NoSuchFieldException e)  {
            return 0;
        }
        
    }


    public void testInitZorba()
    {
        JZorba jZorba = new JZorba();

        String[] privatePtrFields = {
            "cZorbaProxy"
        };

        for (String s: privatePtrFields) {
            assertTrue(getJZorbaPrivatePointerField(jZorba, s) > 0);
        };
    }

    public void testAddGetURIPath() {
        
        JZorba jZorba = new JZorba();

        jZorba.addURIPath("/tmp");

        String[] uriPath = jZorba.getURIPath();

        for (String u: uriPath) {
            System.out.println(String.format("uri path fragment: %s", u));
        };
        // URI Path is empty by default.
        assertTrue(uriPath.length == 1);
        // Trailing slash is added by Zorba internally.
        assertEquals(uriPath[0], "/tmp/");

    }

    public void testCompileQuery() {
        JZorba jZorba = new JZorba();

        String queryString = String.join(
            System.getProperty("line.separator"),
            "declare function local:factorial($N as xs:integer?) as xs:integer {",
            "   if ($N <= 1) then",
            "       1",
            "   else",
            "       $N * local:factorial($N - 1)",
            "};",
            "local:factorial(12)"
        );

        JZorbaQuery query = jZorba.compileQuery(queryString);
        String result = query.execute();
        assertEquals(result, "479001600");
    }

    public void testLoadQueryDocument() {
        JZorba jZorba = new JZorba();

        String queryString = String.join(
            System.getProperty("line.separator"),
            "let s1 = /root/child/li/s[1];",
            "let s2 = /root/child/li/s[2];",
            "return string-join((s1, s2, \"!\"), ' ')"
        );

        String documentString = String.join(
            System.getProperty("line.separator"),
            "<root>",
            "   <child>",
            "       <li><s>Hello</s></li>",
            "       <li><s>Zorba</s></li>",
            "   </child>",
            "</root>"
        );

        JZorbaQuery query = jZorba.compileQuery(queryString);
        query.loadContextDocument(documentString);
        String result = query.execute();
        assertEquals(result, "Hello Zorba !");
    }

}
