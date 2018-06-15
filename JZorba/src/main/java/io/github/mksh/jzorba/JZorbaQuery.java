package io.github.mksh.jzorba;

/**
 * Contains Java Zorba Query native interface.
 *
 * @author mksh
 */
public class JZorbaQuery {

    /**
     *  Holds a pointer value,
     *   containing heap native Zorba compiled query object location.
     */
	private long cZorbaQryProxy;

    private String querySource;

    private String queryError;
    private String queryErrorSourceURI;
    private String queryErrorSourceLine;

    private JZorba zorba;

	public JZorbaQuery(JZorba zorba, String querySource) {
        this.zorba = zorba;
		this.querySource = querySource;
        this.cZorbaQryProxy = 0;
        this.queryError = null;
	};

    public void compile() throws JZorbaError {
        if (!this.isCompiled()) {
            this.doCompile(this.zorba);
        };
    };


    /**
     * Load a document into query context.
     */
    private native void doLoadContextDocument(String documentContent) throws JZorbaError;

    /**
     * Recompile a query
     */
    private native void doCompile(JZorba zorba)  throws JZorbaError;

    public Boolean isCompiled() {
        // After compilation which produced an error, query proxy is not removed yet
        return (cZorbaQryProxy > 0) && (!hasError());
    };

    public Boolean hasError() {
        return queryError != null;
    };

    public String getErrorMessage() {
        return this.queryError;
    };

    public String[] getErrorDetail() {
        String[] resultArr = {
            this.queryError,
            this.queryErrorSourceURI,
            this.queryErrorSourceLine
        };
        return resultArr;
    };

    public void loadContextDocument(String documentContent)  throws JZorbaError {
        this.compile();
        this.doLoadContextDocument(documentContent);
    };

    /**
     * Execute a query, return result XML string.
     */
    public native String execute()  throws JZorbaError;

    /**
     * Set previously loaded document as query context.
     */
    public native void setContextDocument(String documentName);

    // public native void bind(String name, String value);

};
