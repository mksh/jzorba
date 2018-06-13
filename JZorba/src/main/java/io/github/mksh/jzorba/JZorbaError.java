package io.github.mksh.jzorba;


/**
 * Contains Java Zorba exception data.
 *
 * @author mksh
 */
public class JZorbaError {

    // Query caused an error.
    private JZorbaQuery query;
    
    // Execution time error.
    private String executionTimeError;

    JZorbaError(JZorbaQuery query) {
        this.query = query;
        this.executionTimeError = null;
    };

    public void setExecutionTimeError(String error) {
        this.executionTimeError = error;
    };

    public String toString() {
        Boolean isExecutionError = (this.executionTimeError == null);
        String exceptionType = (isExecutionError) ? "XQueryCompilationProblem" : "XQueryExecutionProblem";
        String exceptionMessage;
        if (isExecutionError) {
            exceptionMessage = this.executionTimeError;
        } else {
            String[] errorDetail = this.query.getErrorDetail();
            exceptionMessage = String.format("uri=%s line=%s %s", errorDetail[0], errorDetail[1], errorDetail[2]);
        };
        return String.format("<%s %s>", exceptionType, exceptionMessage);
    };

};