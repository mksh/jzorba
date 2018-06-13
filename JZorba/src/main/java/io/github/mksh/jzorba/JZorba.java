package io.github.mksh.jzorba;

import java.io.*;


/**
 * Contains Java Zorba native interface.
 *
 * @author mksh
 */
public class JZorba {

    public static Boolean isDynLibLoaded = false;
    public static Boolean isDynLibInitialized = false;
    /**
     *   cZorba* values - pointer value, pointing to C++ JZorbaProxy structure.
     *   
     */
	private static long cZorbaProxy;

    /**
     *  Boolean flags.
     */
    private long isDebug;

	public JZorba() {

        // Load native library.
        if (!this.isDynLibLoaded) {
            System.loadLibrary("jzorba");
            this.isDynLibLoaded = true;
        }

        if (!this.isDynLibInitialized) {
            // Initialize native library.
		    this.initZorba();
            this.isDynLibInitialized = true;
        };

        // Deduce debug state from environment variable.
        if (System.getenv("JZORBADEBUG") == "1") {
            this.isDebug = 1;
        } else {
            this.isDebug = 0;
        }

	};

    public Boolean getDebug() {
        return (this.isDebug == 1) ? true: false;
    };

    public JZorbaQuery compileQuery(String querySource) {
        JZorbaQuery query = new JZorbaQuery(this, querySource);
        query.compile();
        return query;
    };

    public static void close() {
        JZorba.shutdownZorba();
        JZorba.isDynLibInitialized = false;
        JZorba.isDynLibLoaded = false;
    };

    private static native void initZorba();

    public static native void shutdownZorba();

    public native void addURIPath(String path);

    public native String[] getURIPath();

    public native void loadDocument(String documentPath, String documentContent);

    public native String getDocument(String documentPath);

    public native Boolean removeDocument(String documentPath);

    // public native registerContextFunction();

};
