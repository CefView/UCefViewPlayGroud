//
//  Copyright © 2025 SHEEN TECH LAB. All Rights Reserved.
//
//! @file CefViewSettings.h
//! @brief Declares the FCefViewSettings class.
#pragma once

#pragma region <Engine Headers>
// Core/Public/
#include <Containers/UnrealString.h>
#include <Math/Color.h>
// CoreUObject/Public/
#include <UObject/ObjectMacros.h>
#pragma endregion

#pragma region <Project Public Headers>
#include <CefViewTypes.h>
#pragma endregion

#pragma region "Generated Header"
#include "CefViewSettings.generated.h"
#pragma endregion

/// <summary>
/// FCefViewSettings defines per-instance configuration for a CEF browser embedded in a UMG widget.
/// It allows fine-grained control over browser appearance, font preferences, encoding, language,
/// and a wide range of browser features such as JavaScript, plugins, storage, and WebGL.
/// Most settings are applied at browser creation and cannot be changed at runtime.
/// Feature toggles use ECefViewFeatureState to enable, disable, or inherit the global/default behavior.
/// All these values are not changeable after one SCefView instance created.
/// </summary>
USTRUCT(BlueprintType)
struct UCEFVIEW_API FCefViewSettings
{
  GENERATED_BODY()

  /// <summary>
  /// The background color of the CEF browser viewport.
  /// Used when no web content is loaded or as the default background.
  /// Default: FColor::White
  /// </summary>
  UPROPERTY(             //
    EditAnywhere,        //
    BlueprintReadWrite,  //
    Category = "Default" //
  )
  FColor BackgroundColor = FColor::White;

  /// <summary>
  /// The font family name used as the standard (proportional) font for web content.
  /// Example: "Arial", "Times New Roman"
  /// </summary>
  UPROPERTY(             //
    EditAnywhere,        //
    BlueprintReadWrite,  //
    Category = "Default" //
  )
  FString StandardFontFamily;

  /// <summary>
  /// The font family name used for fixed-width (monospace) text.
  /// Example: "Courier New", "Consolas"
  /// </summary>
  UPROPERTY(             //
    EditAnywhere,        //
    BlueprintReadWrite,  //
    Category = "Default" //
  )
  FString FixedFontFamily;

  /// <summary>
  /// The font family name used for serif text.
  /// Example: "Times New Roman"
  /// </summary>
  UPROPERTY(             //
    EditAnywhere,        //
    BlueprintReadWrite,  //
    Category = "Default" //
  )
  FString SerifFontFamily;

  /// <summary>
  /// The font family name used for sans-serif text.
  /// Example: "Arial", "Helvetica"
  /// </summary>
  UPROPERTY(             //
    EditAnywhere,        //
    BlueprintReadWrite,  //
    Category = "Default" //
  )
  FString SansSerifFontFamily;

  /// <summary>
  /// The font family name used for cursive text.
  /// Example: "Comic Sans MS"
  /// </summary>
  UPROPERTY(             //
    EditAnywhere,        //
    BlueprintReadWrite,  //
    Category = "Default" //
  )
  FString CursiveFontFamily;

  /// <summary>
  /// The font family name used for fantasy text.
  /// Example: "Impact"
  /// </summary>
  UPROPERTY(             //
    EditAnywhere,        //
    BlueprintReadWrite,  //
    Category = "Default" //
  )
  FString FantasyFontFamily;

  /// <summary>
  /// The default font size (in pixels) for proportional fonts in web content.
  /// Determines the base size for most text.
  /// </summary>
  UPROPERTY(                             //
    EditAnywhere,                        //
    BlueprintReadWrite,                  //
    Category = "Default",                //
    meta = (ClampMin = "0", UIMin = "0") //
  )
  int32 DefaultFontSize = 0;

  /// <summary>
  /// The default font size (in pixels) for fixed-width (monospace) fonts.
  /// Used for code blocks and preformatted text.
  /// </summary>
  UPROPERTY(                             //
    EditAnywhere,                        //
    BlueprintReadWrite,                  //
    Category = "Default",                //
    meta = (ClampMin = "0", UIMin = "0") //
  )
  int32 DefaultFixedFontSize = 0;

  /// <summary>
  /// The minimum font size (in pixels) allowed for any text.
  /// Ensures text remains legible even if web content requests smaller sizes.
  /// </summary>
  UPROPERTY(                             //
    EditAnywhere,                        //
    BlueprintReadWrite,                  //
    Category = "Default",                //
    meta = (ClampMin = "0", UIMin = "0") //
  )
  int32 MinimumFontSize = 0;

  /// <summary>
  /// The minimum logical font size (in pixels) allowed for proportional fonts.
  /// Logical font size may differ from physical font size depending on scaling.
  /// </summary>
  UPROPERTY(                             //
    EditAnywhere,                        //
    BlueprintReadWrite,                  //
    Category = "Default",                //
    meta = (ClampMin = "0", UIMin = "0") //
  )
  int32 MinimumLogicalFontSize = 0;

  /// <summary>
  /// The default text encoding for web content.
  /// Example: "UTF-8"
  /// </summary>
  UPROPERTY(             //
    EditAnywhere,        //
    BlueprintReadWrite,  //
    Category = "Default" //
  )
  FString DefaultEncoding;

  /// <summary>
  /// A comma-separated list of language codes (e.g., "en-US,fr,de") used for the "Accept-Language" HTTP header.
  /// Specifies the preferred languages for web content.
  /// </summary>
  UPROPERTY(             //
    EditAnywhere,        //
    BlueprintReadWrite,  //
    Category = "Default" //
  )
  FString AcceptLanguageList;

  /// <summary>
  /// Controls whether remote web fonts (such as Google Fonts) are enabled or disabled.
  /// ECefViewFeatureState::Default inherits the global or engine default.
  /// </summary>
  UPROPERTY(             //
    EditAnywhere,        //
    BlueprintReadWrite,  //
    Category = "Default" //
  )
  ECefViewFeatureState RemoteFonts = ECefViewFeatureState::Default;

  /// <summary>
  /// Controls whether JavaScript execution is enabled in the browser.
  /// ECefViewFeatureState::Default inherits the global or engine default.
  /// </summary>
  UPROPERTY(             //
    EditAnywhere,        //
    BlueprintReadWrite,  //
    Category = "Default" //
  )
  ECefViewFeatureState Javascript = ECefViewFeatureState::Default;

  /// <summary>
  /// Controls whether JavaScript is allowed to close browser windows (e.g., via window.close()).
  /// ECefViewFeatureState::Default inherits the global or engine default.
  /// </summary>
  UPROPERTY(             //
    EditAnywhere,        //
    BlueprintReadWrite,  //
    Category = "Default" //
  )
  ECefViewFeatureState AllowJavascriptCloseWindows = ECefViewFeatureState::Default;

  /// <summary>
  /// Controls whether JavaScript is allowed to access the system clipboard.
  /// ECefViewFeatureState::Default inherits the global or engine default.
  /// </summary>
  UPROPERTY(             //
    EditAnywhere,        //
    BlueprintReadWrite,  //
    Category = "Default" //
  )
  ECefViewFeatureState AllowJavascriptAccessClipboard = ECefViewFeatureState::Default;

  /// <summary>
  /// Controls whether JavaScript is allowed to perform DOM paste operations.
  /// ECefViewFeatureState::Default inherits the global or engine default.
  /// </summary>
  UPROPERTY(             //
    EditAnywhere,        //
    BlueprintReadWrite,  //
    Category = "Default" //
  )
  ECefViewFeatureState AllowJavascriptDomPaste = ECefViewFeatureState::Default;

  /// <summary>
  /// Controls whether browser plugins (such as Flash, PDF viewers) are enabled.
  /// ECefViewFeatureState::Default inherits the global or engine default.
  /// </summary>
  UPROPERTY(             //
    EditAnywhere,        //
    BlueprintReadWrite,  //
    Category = "Default" //
  )
  ECefViewFeatureState Plugins = ECefViewFeatureState::Default;

  /// <summary>
  /// Controls whether images are loaded automatically in web content.
  /// ECefViewFeatureState::Default inherits the global or engine default.
  /// </summary>
  UPROPERTY(             //
    EditAnywhere,        //
    BlueprintReadWrite,  //
    Category = "Default" //
  )
  ECefViewFeatureState ImageLoading = ECefViewFeatureState::Default;

  /// <summary>
  /// Controls whether standalone images are automatically shrunk to fit the view.
  /// ECefViewFeatureState::Default inherits the global or engine default.
  /// </summary>
  UPROPERTY(             //
    EditAnywhere,        //
    BlueprintReadWrite,  //
    Category = "Default" //
  )
  ECefViewFeatureState ImageShrinkStandaloneToFit = ECefViewFeatureState::Default;

  /// <summary>
  /// Controls whether text areas in web content can be resized by the user.
  /// ECefViewFeatureState::Default inherits the global or engine default.
  /// </summary>
  UPROPERTY(             //
    EditAnywhere,        //
    BlueprintReadWrite,  //
    Category = "Default" //
  )
  ECefViewFeatureState TextAreaResize = ECefViewFeatureState::Default;

  /// <summary>
  /// Controls whether the Tab key can be used to navigate to links in web content.
  /// ECefViewFeatureState::Default inherits the global or engine default.
  /// </summary>
  UPROPERTY(             //
    EditAnywhere,        //
    BlueprintReadWrite,  //
    Category = "Default" //
  )
  ECefViewFeatureState TabToLinks = ECefViewFeatureState::Default;

  /// <summary>
  /// Controls whether HTML5 local storage is enabled for web content.
  /// ECefViewFeatureState::Default inherits the global or engine default.
  /// </summary>
  UPROPERTY(             //
    EditAnywhere,        //
    BlueprintReadWrite,  //
    Category = "Default" //
  )
  ECefViewFeatureState LocalStorage = ECefViewFeatureState::Default;

  /// <summary>
  /// Controls whether HTML5 databases (WebSQL, IndexedDB) are enabled for web content.
  /// ECefViewFeatureState::Default inherits the global or engine default.
  /// </summary>
  UPROPERTY(             //
    EditAnywhere,        //
    BlueprintReadWrite,  //
    Category = "Default" //
  )
  ECefViewFeatureState Databases = ECefViewFeatureState::Default;

  /// <summary>
  /// Controls whether WebGL (hardware-accelerated 3D graphics) is enabled for web content.
  /// ECefViewFeatureState::Default inherits the global or engine default.
  /// </summary>
  UPROPERTY(             //
    EditAnywhere,        //
    BlueprintReadWrite,  //
    Category = "Default" //
  )
  ECefViewFeatureState WebGL = ECefViewFeatureState::Default;
};
