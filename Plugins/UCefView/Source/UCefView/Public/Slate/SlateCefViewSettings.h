//
//  Copyright © 2025 SHEEN TECH LAB. All Rights Reserved.
//
//! @file SlateCefViewSettings.h
//! @brief Declares the FSlateCefViewSettings structure
#pragma once

#pragma region <Engine Headers>
// Core/Public/
#include <Containers/UnrealString.h>
#include <HAL/Platform.h>
// CoreUObject/Public/
#include <UObject/ObjectMacros.h>
#pragma endregion

#pragma region <Project Public Headers>
#include <CefViewTypes.h>
#pragma endregion

/// <summary>
/// Represents the per-instance settings for a Slate-based CefView widget.
/// These settings control font sizes, font families, encoding, language preferences,
/// background color, and a variety of browser features such as JavaScript, plugins,
/// image loading, storage, and more. Most settings are fixed and cannot be changed
/// after the SCefView instance is created. Feature toggles use ECefViewFeatureState
/// to allow enabling, disabling, or inheriting the default behavior for each feature.
/// All these values are not changeable after one SCefView instance created.
/// </summary>
struct UCEFVIEW_API FSlateCefViewSettings
{
  /// <summary>
  /// The default font size (in pixels) used for web content rendering.
  /// This value determines the base size for proportional fonts.
  /// </summary>
  int32 DefaultFontSize;

  /// <summary>
  /// The default font size (in pixels) for fixed-width (monospace) fonts.
  /// Used for code blocks and preformatted text.
  /// </summary>
  int32 DefaultFixedFontSize;

  /// <summary>
  /// The minimum font size (in pixels) allowed for any text.
  /// Ensures text remains legible even if web content requests smaller sizes.
  /// </summary>
  int32 MinimumFontSize;

  /// <summary>
  /// The minimum logical font size (in pixels) allowed for proportional fonts.
  /// Logical font size may differ from physical font size depending on scaling.
  /// </summary>
  int32 MinimumLogicalFontSize;

  /// <summary>
  /// The background color of the browser view.
  /// Used when no web content is loaded or as the default background.
  /// Default: FColor::White
  /// </summary>
  FColor BackgroundColor = FColor::White;

  /// <summary>
  /// The font family name used as the standard (proportional) font for web content.
  /// Example: "Arial", "Times New Roman"
  /// </summary>
  FString StandardFontFamily;

  /// <summary>
  /// The font family name used for fixed-width (monospace) text.
  /// Example: "Courier New", "Consolas"
  /// </summary>
  FString FixedFontFamily;

  /// <summary>
  /// The font family name used for serif text.
  /// Example: "Times New Roman"
  /// </summary>
  FString SerifFontFamily;

  /// <summary>
  /// The font family name used for sans-serif text.
  /// Example: "Arial", "Helvetica"
  /// </summary>
  FString SansSerifFontFamily;

  /// <summary>
  /// The font family name used for cursive text.
  /// Example: "Comic Sans MS"
  /// </summary>
  FString CursiveFontFamily;

  /// <summary>
  /// The font family name used for fantasy text.
  /// Example: "Impact"
  /// </summary>
  FString FantasyFontFamily;

  /// <summary>
  /// The default text encoding for web content.
  /// Example: "UTF-8"
  /// </summary>
  FString DefaultEncoding;

  /// <summary>
  /// A comma-separated list of language codes (e.g., "en-US,fr,de") used for the "Accept-Language" HTTP header.
  /// Specifies the preferred languages for web content.
  /// </summary>
  FString AcceptLanguageList;

  /// <summary>
  /// Controls whether remote web fonts (such as Google Fonts) are enabled or disabled.
  /// Uses ECefViewFeatureState to allow enable, disable, or inherit default behavior.
  /// </summary>
  ECefViewFeatureState RemoteFonts = ECefViewFeatureState::Default;

  /// <summary>
  /// Controls whether JavaScript execution is enabled in the browser.
  /// Default is ECefViewFeatureState::Default (inherits global/default setting).
  /// </summary>
  ECefViewFeatureState Javascript = ECefViewFeatureState::Default;

  /// <summary>
  /// Controls whether JavaScript is allowed to close browser windows (e.g., via window.close()).
  /// Default is ECefViewFeatureState::Default (inherits global/default setting).
  /// </summary>
  ECefViewFeatureState AllowJavascriptCloseWindows = ECefViewFeatureState::Default;

  /// <summary>
  /// Controls whether JavaScript is allowed to access the system clipboard.
  /// Default is ECefViewFeatureState::Default (inherits global/default setting).
  /// </summary>
  ECefViewFeatureState AllowJavascriptAccessClipboard = ECefViewFeatureState::Default;

  /// <summary>
  /// Controls whether JavaScript is allowed to perform DOM paste operations.
  /// Default is ECefViewFeatureState::Default (inherits global/default setting).
  /// </summary>
  ECefViewFeatureState AllowJavascriptDomPaste = ECefViewFeatureState::Default;

  /// <summary>
  /// Controls whether browser plugins (such as Flash, PDF viewers) are enabled.
  /// Default is ECefViewFeatureState::Default (inherits global/default setting).
  /// </summary>
  ECefViewFeatureState Plugins = ECefViewFeatureState::Default;

  /// <summary>
  /// Controls whether images are loaded automatically in web content.
  /// Default is ECefViewFeatureState::Default (inherits global/default setting).
  /// </summary>
  ECefViewFeatureState ImageLoading = ECefViewFeatureState::Default;

  /// <summary>
  /// Controls whether standalone images are automatically shrunk to fit the view.
  /// Default is ECefViewFeatureState::Default (inherits global/default setting).
  /// </summary>
  ECefViewFeatureState ImageShrinkStandaloneToFit = ECefViewFeatureState::Default;

  /// <summary>
  /// Controls whether text areas in web content can be resized by the user.
  /// Default is ECefViewFeatureState::Default (inherits global/default setting).
  /// </summary>
  ECefViewFeatureState TextAreaResize = ECefViewFeatureState::Default;

  /// <summary>
  /// Controls whether the Tab key can be used to navigate to links in web content.
  /// Default is ECefViewFeatureState::Default (inherits global/default setting).
  /// </summary>
  ECefViewFeatureState TabToLinks = ECefViewFeatureState::Default;

  /// <summary>
  /// Controls whether HTML5 local storage is enabled for web content.
  /// Default is ECefViewFeatureState::Default (inherits global/default setting).
  /// </summary>
  ECefViewFeatureState LocalStorage = ECefViewFeatureState::Default;

  /// <summary>
  /// Controls whether HTML5 databases (WebSQL, IndexedDB) are enabled for web content.
  /// Default is ECefViewFeatureState::Default (inherits global/default setting).
  /// </summary>
  ECefViewFeatureState Databases = ECefViewFeatureState::Default;

  /// <summary>
  /// Controls whether WebGL (hardware-accelerated 3D graphics) is enabled for web content.
  /// Default is ECefViewFeatureState::Default (inherits global/default setting).
  /// </summary>
  ECefViewFeatureState WebGL = ECefViewFeatureState::Default;
};
