package com.github.meshotron2.cli_utils.menu.input;

import com.github.meshotron2.cli_utils.exceptions.MenuException;
import com.github.meshotron2.cli_utils.menu.Menu;

import java.util.Scanner;

public class MenuChoice extends NumericInput {

    private final Menu menu;

    /**
     * Creates an Input.
     *
     * @param prompt  The prompt text
     * @param scanner The scanner to be used to handle input
     * @param message The message to be displayed so the user knows what input is expected
     * @param menu    The menu to which this choice belongs
     */
    public MenuChoice(String prompt, Scanner scanner, String message, Menu menu) {
        super(prompt, scanner, message, Integer.class);
        this.menu = menu;
    }

    @Override
    public Number get(String data) throws MenuException {
        final int choice = (int) super.get(data);
        if (choice < 0) throw new MenuException("Invalid option");

        final int nOptions = menu.getOptions().size();
        if (choice > nOptions) throw new MenuException("Invalid option");

        return choice;
    }
}
