package com.github.meshotron2.room_partitioner.cli;

import com.github.meshotron2.cli_utils.menu.Menu;
import com.github.meshotron2.room_partitioner.Main;
import com.github.meshotron2.room_partitioner.partitioner.Partitioner;
import com.github.meshotron2.room_partitioner.partitioner.Room;

import java.util.Arrays;
import java.util.Scanner;

public class MainMenu extends Menu {

    private Partitioner partitioner;

    public MainMenu(Scanner scanner) {
        super(Arrays.asList("0) Select file", "1) Partition room", "2) Exit"),
                Main.PROMPT, scanner, "Select an option");
    }

    @Override
    protected void choose(int option) {
        switch (option) {
            case 0:
                final String fileName = new FileInput(getScanner()).validate();
                this.partitioner = new Partitioner(fileName);
                break;
            case 1:
                final Room room = new PartitionerInputSequence(getScanner()).validate();
                break;
            case 2:
                getScanner().close();
                System.exit(0);
                break;
        }
    }
}
