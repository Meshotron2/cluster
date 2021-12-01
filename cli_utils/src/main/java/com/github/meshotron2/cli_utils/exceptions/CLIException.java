package com.github.meshotron2.cli_utils.exceptions;

/**
 * Base class of all exceptions for this api.
 */
public abstract class CLIException extends Exception {
    protected CLIException(String userMessage) {
        super(userMessage);
    }

    /**
     * Shows the message to the user
     */
    public abstract void display();
}
