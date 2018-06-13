JZorba
======

JZorba is a package which provides JNI binding to Zorba XQuery Processor 3.0+.

See https://github.com/28msec/zorba/ for details on Zorba XQuery Processor.

Requirements
------------

You'll need the following:
- JDK (Java8+)
- JNI header files for your JDK version
- c++ compiler (as Zorba exposes its native API in C++ headers), tested with gcc-c++ 5.4.0
- maven
- ant
- cmake
- make

Usage
-----

```bash
git clone https://github.com/mksh/jzorba
cd jzorba
mvn package
```

How it works
------------

```java

  import io.github.mksh.jzorba.*;

  public class Test {

    public void  testZorba() {
        JZorba jZorba = new JZorba();

        String queryString = String.join(
            System.getProperty("line.separator"),
            "declare function local:factorial($N as xs:integer?) as xs:integer {",
            "   if ($N <= 1) then",
            "       1",
            "   else",
            "       $N * local:factorial($N - 1)",
            "};",
            "local:factorial(4)",
        );

        JZorbaQuery query = jZorba.compileQuery(queryString);
        String result = query.execute();
        assertEquals(result, "24");
    };
  }
```

- JZorba is really instantiated once (C++ Zorba store state is bound to Java static class attribute)

Limitations / possible improvements
-----------------------------------

1. JZorba currently works only on Linux
2. JZorbaQuery is barely serializable

**Patches welcome!**

Credits
-------

0. Zorba development community for bringing in this fantastic open-source effort
1. <https://github.com/gkubisa/jni-maven> - *jni-maven* by gkubisa for getting on the wheels with Maven build
2. <https://oracle.com> - for hosting world-class Java (and JNI) API documentation online


License
-------

MIT.
