/*
 * edtaa3()
 *
 * Sweep-and-update Euclidean distance transform of an
 * image. Positive pixels are treated as object pixels,
 * zero or negative pixels are treated as background.
 * An attempt is made to treat antialiased edges correctly.
 * The input image must have pixels in the range [0,1],
 * and the antialiased image should be a box-filter
 * sampling of the ideal, crisp edge.
 * If the antialias region is more than 1 pixel wide,
 * the result from this transform will be inaccurate.
 *
 * By Stefan Gustavson (stefan.gustavson@gmail.com).
 *
 * Originally written in 1994, based on a verbal
 * description of Per-Erik Danielsson's SSED8 algorithm
 * as presented in the PhD dissertation of Ingemar
 * Ragnemalm. This is Per-Erik Danielsson's scanline
 * scheme from 1979 - I only implemented it in C.
 *
 * Updated in 2004 to treat border pixels correctly,
 * and cleaned up the code to improve readability.
 *
 * Updated in 2009 to handle anti-aliased edges,
 * as published in the article "Anti-aliased Euclidean
 * distance transform" by Stefan Gustavson and Robin Strand,
