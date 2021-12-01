package com.github.meshotron2.room_partitioner.partitioner;

public class Room {
    private final int xg;
    private final int yg;
    private final int zg;

    public Room(int xg, int yg, int zg) {
        this.xg = xg;
        this.yg = yg;
        this.zg = zg;
    }

    @Override
    public String toString() {
        return "Room{" +
                "xg=" + xg +
                ", yg=" + yg +
                ", zg=" + zg +
                '}';
    }
}
