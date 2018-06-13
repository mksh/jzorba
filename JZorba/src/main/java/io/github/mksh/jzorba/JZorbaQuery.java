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

    public synchronized void compile() {
        if (!this.isCompiled()) {
            this.doCompile(zorba);
        };
    };


    /**
     * Load a document into query context.
     */
    private native void doLoadContextDocument(String documentContent);

    /**
     * Recompile a query
     */
    private native void doCompile(JZorba zorba);

    public Boolean isCompiled() {
        // After compilation which produced an error, query proxy is not removed yet
        return (cZorbaQryProxy > 0) && (!hasError());
    };

    public Boolean hasError() {
        return queryError != null;
    };

    public String[] getErrorDetail() {
        String[] resultArr = {
            new String(this.queryError),
            new String(this.queryErrorSourceURI),
            new String(this.queryErrorSourceLine)
        };
        return resultArr;
    };

    public void loadContextDocument(String documentContent) {
        this.compile();
        this.doLoadContextDocument(documentContent);
    };

    /**
     * Execute a query, return result XML string.
     */
    public native String execute();

    /**
     * Set previously loaded document as query context.
     */
    public native void setContextDocument(String documentName);

    // public native void bind(String name, String value);

};
