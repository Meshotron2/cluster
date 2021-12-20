package com.github.meshotron2.cli_utils;

import com.github.meshotron2.cli_utils.menu.Menu;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class CLI {
    private final Scanner s = new Scanner(System.in);
    private final List<Menu> menus = new ArrayList<>();

    public void addMenu(Menu menu) {
        menus.add(menu);
    }

    public void start() {
        start(0);
    }

    public void start(int i) {
        while (true)
            menus.get(i).display();
    }

    public Scanner getS() {
        return s;
    }
}
