package kgms;

public enum ImageFormat {
    JPG (true, false, null),
    JPEG (true, false, null),
    PNG (true, true, new Channel[]{Channel.RED, Channel.GREEN, Channel.BLUE, Channel.ALPHA}),
    BMP (true, true, new Channel[]{Channel.RED, Channel.GREEN, Channel.BLUE, Channel.ALPHA}),
    PPM (true, true, new Channel[]{Channel.RED, Channel.GREEN, Channel.BLUE}),
    PGM (true, true, new Channel[]{Channel.GRAY});
    private boolean allowOut;
    private boolean allowIn;
    private Channel[] allowedChannels;
    ImageFormat(boolean in, boolean out, Channel[] c){
        allowOut = out;
        allowIn = in;
        allowedChannels = c;
    }
    public boolean getAllowOut(){
        return allowOut;
    }
    public boolean getAllowIn(){
        return allowIn;
    }
    public Channel[] getAllowedChannels(){
        return allowedChannels;
    }
    public boolean isAllowedChannel(Channel c1){
        for (Channel c2 : allowedChannels)
            if (c2.equals(c1))
                return true;
        return false;
    }
    public boolean areAllowedChannels(Channel[] c1){
        for (Channel c : c1)
            if (!isAllowedChannel(c))
                return false;
        return true;
    }
}
