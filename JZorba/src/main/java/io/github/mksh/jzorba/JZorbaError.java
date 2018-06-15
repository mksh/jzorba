package io.github.mksh.jzorba;


/**
 * Contains Java Zorba exception data.
 *
 * @author mksh
 */
public class JZorbaError extends Exception {

    // Query caused an error.
    private JZorbaQuery query;

    JZorbaError(JZorbaQuery query) {
        super(query.getErrorMessage());
        this.query = query;
    };

};
