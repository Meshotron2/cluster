package com.github.meshotron2.cli_utils.menu.input;

import com.github.meshotron2.cli_utils.exceptions.MenuException;

import java.util.Scanner;

public class NumericInput extends Input<Number> {

    private final Class<? extends Number> numberClass;

    /**
     * Creates an Input.
     *
     * @param prompt      The prompt text
     * @param scanner     The scanner to be used to handle input
     * @param message     The message to be displayed so the user knows what input is expected
     * @param numberClass The class of the number to be given. It must be one of the below,
     *                    or else the {@link #get(String)} method will throw an {@link IllegalArgumentException}
     *                    <ul>
     *                                       <li>
     *                                       {@link Byte}
     *                                       </li>
     *                                       <li>
     *                                       {@link Short}
     *                                       </li>
     *                                       <li>
     *                                       {@link Integer}
     *                                       </li>
     *                                       <li>
     *                                       {@link Double}
     *                                       </li>
     *                                       <li>
     *                                       {@link Float}
     *                                       </li>
     *                    </ul>
     */
    public NumericInput(String prompt, Scanner scanner, String message, Class<? extends Number> numberClass) {
        super(prompt, scanner, message);
        this.numberClass = numberClass;
    }

    @Override
    public Number get(String data) throws MenuException {

        try {
            if (Byte.class.equals(numberClass)) return Byte.parseByte(data);

            if (Short.class.equals(numberClass)) return Short.parseShort(data);

            if (Integer.class.equals(numberClass)) return Integer.parseInt(data);

            if (Double.class.equals(numberClass)) return Double.parseDouble(data);

            if (Float.class.equals(numberClass)) return Float.parseFloat(data);

        } catch (NumberFormatException e) {
            throw new MenuException("Malformed data");
        }

        throw new IllegalArgumentException("!CRITICAL! numberClass is not supported");
    }
}
