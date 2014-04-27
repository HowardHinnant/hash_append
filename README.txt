This is a collection of software used to provide an example
implementation of the proposal currently at:

http://htmlpreview.github.io/?https://github.com/HowardHinnant/papers/blob/master/hashing.html

And to demonstrate example software surrounding / using this proposal.

Though there are a lot of files here, only one file contains an implementation
of proposed software:

    hash_append.h

Everything in namespace xstd, except for those things in xstd::detail, is
proposed.  Nothing else is.  The only file containing anything in namespace
xstd is hash_append.h.

Currently hash_append.h is missing hash_append overloads for many std::containers
and other objects.  They should be added.
