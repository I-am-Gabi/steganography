package kgms.message;

import java.io.IOException;

public interface Message {
    int read(byte[] tab) throws IOException;

    long getBytesLeft() throws IOException;

    long getFileSize() throws IOException;

    void reset() throws IOException;

    boolean isEmpty() throws IOException;
}
