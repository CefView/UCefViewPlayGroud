//
//  Copyright © 2025 SHEEN TECH LAB. All Rights Reserved.
//
//! @file CefViewEvent.h
//! @brief Declares the UCefViewEvent class for handling CEF view events.
#pragma once

#pragma region <Engine Headers>
// Core/Public/
#include <Containers/Array.h>
#include <Containers/UnrealString.h>
#include <Templates/PimplPtr.h>
// CoreUObject/Public/
#include <UObject/ObjectMacros.h>
// JsonJson/Public/
#include <Dom/JsonValue.h>
#include <Dom/JsonObject.h>
#pragma endregion

#pragma region <Project Public Headers>
#pragma endregion

#pragma region "Generated Header"
#include "CefViewEvent.generated.h"
#pragma endregion

/// <summary>
/// Represents an event dispatched from the C++ code in native context to the Javascript code in web context.
/// </summary>
/// <remarks>
/// <para>
/// <c>UCefViewEvent</c> encapsulates the name and arguments of an event sent from JavaScript running in a CEF browser
/// instance to the Unreal Engine application. This enables seamless communication between web content and native game
/// logic, allowing you to handle browser-originated events in both Blueprints and C++.
/// </para>
/// <para>
/// Events are typically triggered from C++ code and handled in JavaScript code. Trigger events with the following
/// methods:
/// - UCefView::TriggerEventForFrame
/// - UCefView::TriggerEventForMainFrame
/// - UCefView::BroadcastEvent
/// - SCefView::TriggerEventForFrame
/// - SCefView::TriggerEventForMainFrame
/// - SCefView::BroadcastEvent
/// </para>
/// </remarks>
UCLASS(BlueprintType)
class UCEFVIEW_API UCefViewEvent : public UObject
{
  GENERATED_BODY()

public:
  /// <summary>
  /// The name of the event as dispatched from the browser.
  /// </summary>
  /// <remarks>
  /// <para>
  /// This string identifies the type or purpose of the event (e.g., "OnButtonClick", "DataReceived").
  /// It is set by the C++ code or blueprint in native context and read by JavaScript.
  /// </para>
  /// </remarks>
  UPROPERTY(             //
    EditAnywhere,        //
    BlueprintReadWrite,  //
    Category = "Default" //
  )
  FString Name;

  /// <summary>
  /// Gets the arguments associated with this event in JSON string format to be passed to the JavaScript event handler.
  /// </summary>
  /// <returns>
  /// A string representing the arguments as a JSON array (e.g., <c>[1, "foo", true]</c>).
  /// </returns>
  /// <remarks>
  /// </remarks>
  UFUNCTION(BlueprintCallable, Category = "Default")
  FString GetArguments() const;

  /// <summary>
  /// Sets the arguments for this event using a JSON string.
  /// </summary>
  /// <param name="InArguments">
  /// A string representing the arguments as a JSON array (e.g., <c>[1, "foo", true]</c>).</param>
  /// <remarks>
  /// <para>
  /// Use this method to set the raw arguments as sent to the browser. This method parses the provided JSON
  /// string and updates the <see cref="Arguments"/> property accordingly. The input must be a valid JSON
  /// array; otherwise, parsing will fail and the arguments will not be updated.
  /// </para>
  /// </remarks>
  UFUNCTION(BlueprintCallable, Category = "Default")
  void SetArguments(const FString& InArguments);

  /// <summary>
  /// The parsed arguments associated with the event, represented as an array of JSON values.
  /// </summary>
  /// <remarks>
  /// <para>
  /// Each element in the array corresponds to an argument passed from the browser, and can be a number, string,
  /// boolean, object, or array, depending on the data sent from JavaScript.
  /// </para>
  /// <para>
  /// This property is automatically updated when <see cref="SetArguments"/> is called, and is used internally by
  /// <see cref="GetArguments"/> to serialize the arguments back to a JSON string.
  /// </para>
  /// <para>
  /// Use this property for type-safe access to individual arguments in C++.
  /// </para>
  /// </remarks>
  TArray<TSharedPtr<FJsonValue>> Arguments;
};
