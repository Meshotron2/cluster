package com.github.meshotron2.cli_utils.exceptions;

/**
 * Base class of all exceptions for this api.
 */
public abstract class CLIException extends Exception {
    private final String userMessage;

    protected CLIException(String userMessage) {
        this.userMessage = userMessage;
    }

    /**
     * Shows the message to the user
     */
    public abstract void display();

    public String getUserMessage() {
        return userMessage;
    }
}
