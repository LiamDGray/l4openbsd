#!perl

print "1..39\n";
my $test = 0;

sub failed {
    my ($got, $expected, $name) = @_;

    print "not ok $test - $name\n";
    my @caller = caller(1);
    print "# Failed test at $caller[1] line $caller[2]\n";
    if (defined $got) {
	print "# Got '$got'\n";
    } else {
	print "# Got undef\n";
    }
    print "# Expected $expected\n";
    return;
}

sub like {
    my ($got, $pattern) = @_;
    $test = $test + 1;
    if (defined $got && $got =~ $pattern) {
	print "ok $test\n";
	# Principle of least surprise - maintain the expected interface, even
	# though we aren't using it here (yet).
	return 1;
    }
    failed($got, $pattern, $name);
}

sub is {
    my ($got, $expect) = @_;
    $test = $test + 1;
    if (defined $expect) {
	if (defined $got && $got eq $expect) {
	    print "ok $test\n";
	    return 1;
	}
	failed($got, "'$expect'", $name);
    } else {
	if (!defined $got) {
	    print "ok $test\n";
	    return 1;
	}
	failed($got, 'undef', $name);
    }
}

sub f($$_) { my $x = shift; is("@_", $x) }

$foo = "FOO";
my $bar = "BAR";
$_ = 42;

f("FOO xy", $foo, "xy");
f("BAR zt", $bar, "zt");
f("FOO 42", $foo);
f("BAR 42", $bar);
f("y 42", substr("xy",1,1));
f("1 42", ("abcdef" =~ /abc/));
f("not undef 42", $undef || "not undef");
f(" 42", -f "no_such_file");
f("FOOBAR 42", ($foo . $bar));
f("FOOBAR 42", ($foo .= $bar));
f("FOOBAR 42", $foo);

eval q{ f("foo") };
like( $@, qr/Not enough arguments for main::f at/ );
eval q{ f(1,2,3,4) };
like( $@, qr/Too many arguments for main::f at/ );

{
    my $_ = "quarante-deux";
    $foo = "FOO";
    $bar = "BAR";
    f("FOO quarante-deux", $foo);
    f("BAR quarante-deux", $bar);
    f("y quarante-deux", substr("xy",1,1));
    f("1 quarante-deux", ("abcdef" =~ /abc/));
    f("not undef quarante-deux", $undef || "not undef");
    f(" quarante-deux", -f "no_such_file");
    f("FOOBAR quarante-deux", ($foo . $bar));
    f("FOOBAR quarante-deux", ($foo .= $bar));
    f("FOOBAR quarante-deux", $foo);
}

&f(""); # no error

sub g(_) { is(shift, $expected) }

$expected = "foo";
g("foo");
g($expected);
$_ = $expected;
g();
g;
undef $expected; &g; # $_ not passed
{ $expected = my $_ = "bar"; g() }

eval q{ sub wrong1 (_$); wrong1(1,2) };
like( $@, qr/Malformed prototype for main::wrong1/, 'wrong1' );

eval q{ sub wrong2 ($__); wrong2(1,2) };
like( $@, qr/Malformed prototype for main::wrong2/, 'wrong2' );

sub opt ($;_) {
    is($_[0], "seen");
    is($_[1], undef, "; has precedence over _");
}

opt("seen");

sub unop (_) { is($_[0], 11, "unary op") }
unop 11, 22; # takes only the first parameter into account

sub mymkdir (_;$) { is("@_", $expected, "mymkdir") }
$expected = $_ = "mydir"; mymkdir();
mymkdir($expected = "foo");
$expected = "foo 493"; mymkdir foo => 0755;

# $_ says modifiable, it's not passed by copy

sub double(_) { $_[0] *= 2 }
$_ = 21;
double();
is( $_, 42, '$_ is modifiable' );
{
    my $_ = 22;
    double();
    is( $_, 44, 'my $_ is modifiable' );
}
