package com.github.meshotron2.room_partitioner.cli;

import com.github.meshotron2.cli_utils.exceptions.MenuException;
import com.github.meshotron2.cli_utils.menu.input.InputSequence;
import com.github.meshotron2.room_partitioner.Main;
import com.github.meshotron2.room_partitioner.partitioner.Room;

import java.util.Arrays;
import java.util.Scanner;

public class PartitionerInputSequence extends InputSequence<Room> {
    public PartitionerInputSequence(Scanner scanner) {
        super(Main.PROMPT, scanner, Arrays.asList(
                new PartitionerInput(scanner, "Xg"),
                new PartitionerInput(scanner, "Yg"),
                new PartitionerInput(scanner, "Zg")
        ));
    }

    @Override
    protected Room get(String s) throws MenuException {
        // TODO: 12/1/21 Validate the numbers in group
        return new Room((int) getInputs().get(0).validate(),
                (int) getInputs().get(1).validate(),
                (int) getInputs().get(2).validate());
    }
}
