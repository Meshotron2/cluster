package com.github.meshotron2.cli_utils.menu;

import java.util.HashMap;
import java.util.Map;

/**
 * Manages string replacing so CLI text can be modularized and not so hard coded
 */
public class Formatter {
    private final Map<String, String> replacers = new HashMap<>();

    /**
     * Creates a Formatter
     *
     * @param replacers a {@link Map} that maps a string to be replaced with the desired replacement.
     */
    public Formatter(Map<String, String> replacers) {
        this.replacers.putAll(replacers);
    }

    /**
     * Applies all replacers to the given {@link String}
     *
     * @param s The string to be formatted
     * @return The given string with all replacements applied
     */
    public String resolve(String s) {
        for (Map.Entry<String, String> entry : replacers.entrySet()) {
            String k = entry.getKey();
            String v = entry.getValue();
            s = s.replaceAll(k, v);
        }
        return s;
    }

    /**
     * Applies all replacers, those of the object and those passed in replacers, to the given {@link String}
     *
     * @param s         The string to be formatted
     * @param replacers The replacers that, in addition to those of this object, are to be applied to the string
     * @return The given string with all replacements applied
     */
    public String resolve(String s, Map<String, String> replacers) {
        s = resolve(s);

        for (Map.Entry<String, String> entry : replacers.entrySet()) {
            String k = entry.getKey();
            String v = entry.getValue();
            s = s.replaceAll(k, v);
        }

        return s;
    }
}
