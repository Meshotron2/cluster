package com.github.meshotron2.room_partitioner.partitioner;

import java.util.ArrayList;
import java.util.List;

public class Partitioner {

    private Room room;
    private int xg;
    private int yg;
    private int zg;

    public Partitioner(Room room, int xg, int yg, int zg) {
        this.room = room;
        this.xg = xg;
        this.yg = yg;
        this.zg = zg;
    }

    public List<Room> partition() {
        if (!validate())
            return null;

        

        return new ArrayList<>();
    }

    private boolean validate() {
        return room != null && isCoordsValid();
    }

    public boolean isCoordsValid() {
        // TODO: 12/4/21 validate if the integers make sense for this room
        return xg > 0 && yg > 0 && zg > 0;
    }

    public Room getRoom() {
        return room;
    }

    public void setRoom(Room room) {
        this.room = room;
    }

    public int getXg() {
        return xg;
    }

    public void setXg(int xg) {
        this.xg = xg;
    }

    public int getYg() {
        return yg;
    }

    public void setYg(int yg) {
        this.yg = yg;
    }

    public int getZg() {
        return zg;
    }

    public void setZg(int zg) {
        this.zg = zg;
    }
}
