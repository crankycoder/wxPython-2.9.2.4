/////////////////////////////////////////////////////////////////////////////
// Name:        wx/richtext/richtexthtml.h
// Purpose:     HTML I/O for wxRichTextCtrl
// Author:      Julian Smart
// Modified by:
// Created:     2005-09-30
// RCS-ID:      $Id: richtexthtml.h 67882 2011-06-07 16:48:36Z VZ $
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_RICHTEXTHTML_H_
#define _WX_RICHTEXTHTML_H_

/*!
 * Includes
 */

#include "wx/richtext/richtextbuffer.h"

// Use CSS styles where applicable, otherwise use non-CSS workarounds
#define wxRICHTEXT_HANDLER_USE_CSS 0x1000

/*!
 * wxRichTextHTMLHandler
 */

class WXDLLIMPEXP_RICHTEXT wxRichTextHTMLHandler: public wxRichTextFileHandler
{
    DECLARE_DYNAMIC_CLASS(wxRichTextHTMLHandler)
public:
    wxRichTextHTMLHandler(const wxString& name = wxT("HTML"), const wxString& ext = wxT("html"), int type = wxRICHTEXT_TYPE_HTML);

    /// Can we save using this handler?
    virtual bool CanSave() const { return true; }

    /// Can we load using this handler?
    virtual bool CanLoad() const { return false; }

    /// Can we handle this filename (if using files)? By default, checks the extension.
    virtual bool CanHandle(const wxString& filename) const;

// Accessors and operations unique to this handler

    /// Set and get the list of image locations generated by the last operation
    void SetTemporaryImageLocations(const wxArrayString& locations) { m_imageLocations = locations; }
    const wxArrayString& GetTemporaryImageLocations() const { return m_imageLocations; }

    /// Clear the image locations generated by the last operation
    void ClearTemporaryImageLocations() { m_imageLocations.Clear(); }

    /// Delete the in-memory or temporary files generated by the last operation
    bool DeleteTemporaryImages();

    /// Delete the in-memory or temporary files generated by the last operation. This is a static
    /// function that can be used to delete the saved locations from an earlier operation,
    /// for example after the user has viewed the HTML file.
    static bool DeleteTemporaryImages(int flags, const wxArrayString& imageLocations);

    /// Reset the file counter, in case, for example, the same names are required each time
    static void SetFileCounter(int counter) { sm_fileCounter = counter; }

    /// Set and get the directory for storing temporary files. If empty, the system
    /// temporary directory will be used.
    void SetTempDir(const wxString& tempDir) { m_tempDir = tempDir; }
    const wxString& GetTempDir() const { return m_tempDir; }

    /// Set and get mapping from point size to HTML font size. There should be 7 elements,
    /// one for each HTML font size, each element specifying the maximum point size for that
    /// HTML font size. E.g. 8, 10, 13, 17, 22, 29, 100
    void SetFontSizeMapping(const wxArrayInt& fontSizeMapping) { m_fontSizeMapping = fontSizeMapping; }
    wxArrayInt GetFontSizeMapping() const { return m_fontSizeMapping; }

protected:

// Implementation

#if wxUSE_STREAMS
    virtual bool DoLoadFile(wxRichTextBuffer *buffer, wxInputStream& stream);
    virtual bool DoSaveFile(wxRichTextBuffer *buffer, wxOutputStream& stream);

    /// Output character formatting
    void BeginCharacterFormatting(const wxRichTextAttr& currentStyle, const wxRichTextAttr& thisStyle, const wxRichTextAttr& paraStyle, wxTextOutputStream& stream );
    void EndCharacterFormatting(const wxRichTextAttr& currentStyle, const wxRichTextAttr& thisStyle, const wxRichTextAttr& paraStyle, wxTextOutputStream& stream );

    /// Output paragraph formatting
    void BeginParagraphFormatting(const wxRichTextAttr& currentStyle, const wxRichTextAttr& thisStyle, wxTextOutputStream& stream);
    void EndParagraphFormatting(const wxRichTextAttr& currentStyle, const wxRichTextAttr& thisStyle, wxTextOutputStream& stream);

    /// Output font tag
    void OutputFont(const wxRichTextAttr& style, wxTextOutputStream& stream);

    /// Closes lists to level (-1 means close all)
    void CloseLists(int level, wxTextOutputStream& str);

    /// Writes an image to its base64 equivalent, or to the memory filesystem, or to a file
    void WriteImage(wxRichTextImage* image, wxOutputStream& stream);

    /// Converts from pt to size property compatible height
    long PtToSize(long size);

    /// Typical base64 encoder
    wxChar* b64enc(unsigned char* input, size_t in_len);

    /// Gets the mime type of the given wxBITMAP_TYPE
    const wxChar* GetMimeType(int imageType);

    /// Gets the html equivalent of the specified value
    wxString GetAlignment(const wxRichTextAttr& thisStyle);

    /// Generates &nbsp; array for indentations
    wxString SymbolicIndent(long indent);

    /// Finds the html equivalent of the specified bullet
    int TypeOfList(const wxRichTextAttr& thisStyle, wxString& tag);
#endif

// Data members

    wxRichTextBuffer* m_buffer;

    /// Indentation values of the table tags
    wxArrayInt      m_indents;

    /// Stack of list types: 0 = ol, 1 = ul
    wxArrayInt      m_listTypes;

    /// Is there any opened font tag?
    bool            m_font;

    /// Are we in a table?
    bool            m_inTable;

    /// A list of the image files or in-memory images created by the last operation.
    wxArrayString   m_imageLocations;

    /// A location for the temporary files
    wxString        m_tempDir;

    /// A mapping from point size to HTML font size
    wxArrayInt      m_fontSizeMapping;

    /// A counter for generating filenames
    static int      sm_fileCounter;
};

#endif
    // _WX_RICHTEXTXML_H_
