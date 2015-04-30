package com.example.mike.javabenchmark;

import java.io.IOException;
import java.util.Date;
import java.util.HashSet;
import java.util.Set;
import java.util.UUID;

import android.util.Log;




public class Message {

    public class Folder {

    }

    private static final Flag[] EMPTY_FLAG_ARRAY = new Flag[0];
    //private MessageReference mReference = null;

    public enum RecipientType {
        TO, CC, BCC,
    }

    protected String mUid;

    protected HashSet<Flag> mFlags = new HashSet<Flag>();

    protected Date mInternalDate;
    protected Date mStoredDate;
    protected Folder mFolder;

    public String mText;
    public Date mSentDate;
    public String mSubject;
    public String mFrom;
    public String mId;
    public String[] mRefs;

    public Message(){
        mText = "Some dummy text for now. " + UUID.randomUUID().toString();
        mSubject = "Sample Subject";
        mFrom = "anemail@address.com";
        mSentDate = new Date();
        mInternalDate = new Date();
        mStoredDate = new Date();
    }


    public boolean olderThan(Date earliestDate) {
        if (earliestDate == null) {
            return false;
        }
        Date myDate = getSentDate();
        if (myDate == null) {
            myDate = getInternalDate();
        }
        if (myDate != null) {
            return myDate.before(earliestDate);
        }
        return false;
    }

    @Override
    public boolean equals(Object o) {
        if (o == null || !(o instanceof Message)) {
            return false;
        }
        Message other = (Message) o;
        return (mUid.equals(other.getUid()));
    }

    @Override
    public int hashCode() {
        final int MULTIPLIER = 31;

        int result = 1;
        //result = MULTIPLIER * result + mFolder.getName().hashCode();
        //result = MULTIPLIER * result + mFolder.getAccount().getUuid().hashCode();
        result = MULTIPLIER * result + mUid.hashCode();
        return result;
    }

    public String getUid() {
        return mUid;
    }

    public void setUid(String uid) {
        this.mUid = uid;
    }

    public Folder getFolder() {
        return mFolder;
    }

    public String getSubject() {
        return mSubject;
    }

    public void setSubject(String subject) throws MessagingException {
        mSubject = subject;
    }

    public String getText() {
        return mText;
    }

    public void setText(String text) throws MessagingException {
        mText = text;
    }

    public Date getInternalDate() {
        return mInternalDate;
    }

    public void setInternalDate(Date internalDate) {
        this.mInternalDate = internalDate;
    }

    public Date getStoredDate() {
        return mStoredDate;
    }

    public void setStoredDate(Date storedDate) {
        this.mStoredDate = storedDate;
    }

    public Date getSentDate() {
        return mSentDate;
    }

    public void setSentDate(Date sentDate) throws MessagingException {
        mSentDate = sentDate;
    }

    //public abstract Address[] getRecipients(RecipientType type) throws MessagingException;

    public String getFrom() {
        return mFrom;
    }

    public void setFrom(String from) throws MessagingException {
        mFrom = from;
    }

    public String getReplyTo() {
        return mFrom;
    }

    public void setReplyTo(String from) throws MessagingException {

    }


    public String getMessageId() throws MessagingException {
        return mId;
    }

    public void setInReplyTo(String inReplyTo) throws MessagingException {

    }

    public String[] getReferences() throws MessagingException {
        if( mRefs == null ) {
            mRefs = new String[0];
        }
        return mRefs;
    }

    public void setReferences(String references) throws MessagingException{
        //mRefs = references;
    }


    public boolean hasAttachments(){
        return false;
    }

    /*
     * calculateContentPreview
     * Takes a plain text message body as a string.
     * Returns a message summary as a string suitable for showing in a message list
     *
     * A message summary should be about the first 160 characters
     * of unique text written by the message sender
     * Quoted text, "On $date" and so on will be stripped out.
     * All newlines and whitespace will be compressed.
     *
     */
    public static String calculateContentPreview(String text) {
        if (text == null) {
            return null;
        }

        // Only look at the first 8k of a message when calculating
        // the preview.  This should avoid unnecessary
        // memory usage on large messages
        if (text.length() > 8192) {
            text = text.substring(0, 8192);
        }

        // Remove (correctly delimited by '-- \n') signatures
        text = text.replaceAll("(?ms)^-- [\\r\\n]+.*", "");
        // try to remove lines of dashes in the preview
        text = text.replaceAll("(?m)^----.*?$", "");
        // remove quoted text from the preview
        text = text.replaceAll("(?m)^[#>].*$", "");
        // Remove a common quote header from the preview
        text = text.replaceAll("(?m)^On .*wrote.?$", "");
        // Remove a more generic quote header from the preview
        text = text.replaceAll("(?m)^.*\\w+:$", "");
        // Remove horizontal rules.
        text = text.replaceAll("\\s*([-=_]{30,}+)\\s*", " ");

        // URLs in the preview should just be shown as "..." - They're not
        // clickable and they usually overwhelm the preview
        text = text.replaceAll("https?://\\S+", "...");
        // Don't show newlines in the preview
        text = text.replaceAll("(\\r|\\n)+", " ");
        // Collapse whitespace in the preview
        text = text.replaceAll("\\s+", " ");
        // Remove any whitespace at the beginning and end of the string.
        text = text.trim();

        return (text.length() <= 512) ? text : text.substring(0, 512);
    }

    public void delete(String trashFolderName) throws MessagingException {}

    /*
     * TODO Refactor Flags at some point to be able to store user defined flags.
     */
    public Flag[] getFlags() {
        return mFlags.toArray(EMPTY_FLAG_ARRAY);
    }

    /**
     * @param flag
     *            Flag to set. Never <code>null</code>.
     * @param set
     *            If <code>true</code>, the flag is added. If <code>false</code>
     *            , the flag is removed.
     * @throws MessagingException
     */
    public void setFlag(Flag flag, boolean set) throws MessagingException {
        if (set) {
            mFlags.add(flag);
        } else {
            mFlags.remove(flag);
        }
    }

    /**
     * This method calls setFlag(Flag, boolean)
     * @param flags
     * @param set
     */
    public void setFlags(Flag[] flags, boolean set) throws MessagingException {
        for (Flag flag : flags) {
            setFlag(flag, set);
        }
    }

    public boolean isSet(Flag flag) {
        return mFlags.contains(flag);
    }
    public void destroy() throws MessagingException {}


    /**
     * Copy the contents of this object into another {@code Message} object.
     *
     * @param destination
     *         The {@code Message} object to receive the contents of this instance.
     */
    protected void copy(Message destination) {
        destination.mUid = mUid;
        destination.mInternalDate = mInternalDate;
        destination.mFolder = mFolder;
        //destination.mReference = mReference;
        destination.mStoredDate = mStoredDate;

        // mFlags contents can change during the object lifetime, so copy the Set
        destination.mFlags = new HashSet<Flag>(mFlags);
    }

    /**
     * Creates a new {@code Message} object with the same content as this object.
     *
     * <p>
     * <strong>Note:</strong>
     * This method was introduced as a hack to prevent {@code ConcurrentModificationException}s. It
     * shouldn't be used unless absolutely necessary. See the comment in
     * {@link com.securdataservices.ePGP.activity.MessageView.Listener#loadMessageForViewHeadersAvailable(com.mblsft.smail.Account, String, String, Message)}
     * for more information.
     * </p>
     */


}
