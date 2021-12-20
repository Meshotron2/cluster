package com.github.meshotron2.cli_utils.menu.input;

import com.github.meshotron2.cli_utils.exceptions.MenuException;

import java.util.List;
import java.util.Scanner;

/**
 * Handles the situations where validations require a plethora of input.
 * Can also be used when data to be handled is to be fetched in various phases from the user.
 * <p>
 * It is strongly encouraged to override {@link Input#get(String)} in order to run all
 * Input objects stored in this InputSequence.
 */
public abstract class InputSequence<T> extends Input<T> {

    private final List<? extends Input<?>> inputs;

    /**
     * Creates an InputSequence.
     *
     * @param prompt  The prompt text
     * @param scanner The scanner to be used to handle input
     */
    public InputSequence(String prompt, Scanner scanner, List<? extends Input<?>> inputs) {
        super(prompt, scanner, null);
        this.inputs = inputs;
    }

    @Override
    public T validate() {
        while (true)
            try {
                return get(null);
            } catch (MenuException e) {
                e.display();
            }
    }

    public List<? extends Input<?>> getInputs() {
        return inputs;
    }
}
