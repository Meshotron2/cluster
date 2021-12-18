package com.github.meshotron2.cli_utils.menu.input;

import com.github.meshotron2.cli_utils.exceptions.MenuException;

import java.util.Scanner;

/**
 * Fetches a single line on the console and handles it
 *
 * The implementation of {@link Input#get(String)} must return the parsed and validated input
 *
 * @param <T> The type of the input
 */
public abstract class Input<T>{
    private final Scanner scanner;
    private final String prompt;
    private final String message;

    /**
     * Creates an Input.
     * @param prompt  The prompt text
     * @param scanner The scanner to be used to handle input
     * @param message The message to be displayed so the user knows what input is expected
     */
    public Input(String prompt, Scanner scanner, String message) {
        this.scanner = scanner;
        this.prompt = prompt;
        this.message = message;
    }

    /**
     * Asks for input, calls {@link #get(String)} and returns it's result.
     * If {@link #get(String)} throws any error, this method will show the user that error.
     * @return The parsed input
     */
    public T validate() {
        while (true)
            try {
                final String data = prompt();

                return get(data);
            } catch (MenuException e) {
                e.display();
            }
    }

    public String prompt() {
        if (message != null)
            System.out.println("\n" + message);

        System.out.print(prompt);
        return scanner.nextLine();
    }

    /**
     * Reads the console, validates and parses what the user typed.
     * For an example implementation check {@link NumericInput}
     *
     * @return The input converted into the desired type
     * @param data The input to be parsed
     * @throws MenuException when the data is malformed, wrong or unexpected.
     */
    protected abstract T get(String data) throws MenuException;

    public String getPrompt() {
        return prompt;
    }

    public Scanner getScanner() {
        return scanner;
    }
}
