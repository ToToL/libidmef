#!/usr/bin/perl -w
#

use strict;

push @INC,".";
push @INC,"./perl";
push @INC,"./.libs";

eval  { require LibIdmefEasy; };
die "Could not load LibIdmefEasy ($@).\nTry 'cd ./.libs && ln -s libidmef_perl.so LibIdmefEasy.so'" if $@;

sub PrintUID
{
	print "UID is $<\n";
}

LibIdmefEasy::set_perlmethod(\&PrintUID);

LibIdmefEasy::test_fct();
