package com.github.meshotron2.room_partitioner.partitioner;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;

public class Room {
    private final String file;

    private final int x;
    private final int y;
    private final int z;

    private final long f;

    private Room(String file, int x, int y, int z, long f) {
        this.file = file;
        this.x = x;
        this.y = y;
        this.z = z;
        this.f = f;
    }

    public void readIndices() {
        
    }

    public static Room fromFile(String file) throws IOException {
        final InputStream reader = new FileInputStream(file);

        final byte[] bs = new byte[4];

        int status = reader.read(bs);
        if (status != 4) return null;
        final int x = ((int) bs[0]) << 24 | ((int) bs[1]) << 16 | ((int) bs[2]) << 8 | ((int) bs[3]);

        status = reader.read(bs);
        if (status != 4) return null;
        final int y = ((int) bs[0]) << 24 | ((int) bs[1]) << 16 | ((int) bs[2]) << 8 | ((int) bs[3]);

        status = reader.read(bs);
        if (status != 4) return null;
        final int z = ((int) bs[0]) << 24 | ((int) bs[1]) << 16 | ((int) bs[2]) << 8 | ((int) bs[3]);

        // TODO: 12/6/21 Simplify
        status = reader.read(bs);
        if (status != 4) return null;
        final int f1 = ((int) bs[0]) << 24 | ((int) bs[1]) << 16 | ((int) bs[2]) << 8 | ((int) bs[3]);
        status = reader.read(bs);
        if (status != 4) return null;
        final int f2 = ((int) bs[0]) << 24 | ((int) bs[1]) << 16 | ((int) bs[2]) << 8 | ((int) bs[3]);

        final long f = ((long) f1) << 32 | f2;

        reader.close();
        return new Room(file, x, y, z, f);
    }
}