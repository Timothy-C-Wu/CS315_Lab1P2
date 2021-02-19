This program should run properly and print the line number and character position in brackets followed by the tag.
All features should work properly.
One possible bug is a tag that starts with a number like a malformed tag <5p> will still be printed even though it is not correctly formatted.
This is because I am using the isalnum function which will catch numbers and alphabetical characters.