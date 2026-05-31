//
//  Copyright © 2025 SHEEN TECH LAB. All Rights Reserved.
//
//! @file CefViewQuery.h
//! @brief Declares the UCefViewQuery class, which represents a query from the CEF browser.
#pragma once

#pragma region <Engine Headers>
// Core/Public/
#include <Containers/UnrealString.h>
#include <HAL/Platform.h>
#include <Misc/ScopeLock.h>
// CoreUObject/Public/
#include <UObject/ObjectMacros.h>
#include <UObject/WeakObjectPtrTemplates.h>
#pragma endregion

#pragma region <Project Public Headers>
#pragma endregion

#pragma region "Generated Header"
#include "CefViewQuery.generated.h"
#pragma endregion

/// <summary>
/// Represents a query sent from the CEF (Chromium Embedded Framework) browser to the Unreal Engine.
/// This class encapsulates the query ID, request content, and methods for replying to the query.
/// </summary>
/// <remarks>
/// <para>
/// <c>UCefViewQuery</c> is used to handle asynchronous communication from JavaScript running in a CEF browser instance
/// to the Unreal Engine application. Each query is uniquely identified and can be replied to with a result or error.
/// </para>
/// <para>
/// Queries are typically initiated from JavaScript using the CEF query API, and are received in Unreal as instances of
/// this class. Use the provided methods and properties to inspect the query, process it, and send a response back to
/// the browser.
/// </para>
/// </remarks>
/// <example>
/// Example usage in Blueprint:
/// <code>
/// Event OnCefViewQueryReceived(UCefViewQuery* Query)
/// {
///     if (Query->GetRequest() == "GetData")
///     {
///         Query->IsSuccess = true;
///         Query->Response = "SomeData";
///     }
///     else
///     {
///         Query->IsSuccess = false;
///         Query->ErrorCode = 404;
///         Query->Response = "Not found";
///     }
///     Query->Reply();
/// }
/// </code>
/// </example>
UCLASS(BlueprintType)
class UCEFVIEW_API UCefViewQuery : public UObject
{
  GENERATED_BODY()

public:
  /// <summary>
  /// Indicates whether the query was processed successfully.
  /// </summary>
  /// <remarks>
  /// <para>
  /// Set this property to <c>true</c> if the query was handled successfully, or <c>false</c> if an error occurred.
  /// This value is sent back to the browser as part of the query response.
  /// </para>
  /// </remarks>
  UPROPERTY(             //
    EditAnywhere,        //
    BlueprintReadWrite,  //
    Category = "Default" //
  )
  bool IsSuccess = false;

  /// <summary>
  /// Error code associated with the query, if any.
  /// </summary>
  /// <remarks>
  /// <para>
  /// Set this property to a non-zero value to indicate an error. The meaning of the error code is application-specific.
  /// If <see cref="IsSuccess"/> is <c>true</c>, this value is typically ignored.
  /// </para>
  /// </remarks>
  UPROPERTY(             //
    EditAnywhere,        //
    BlueprintReadWrite,  //
    Category = "Default" //
  )
  int32 ErrorCode = 0;

  /// <summary>
  /// The response data for the query.
  /// </summary>
  /// <remarks>
  /// <para>
  /// Set this property to the string data you wish to return to the browser as the result of the query.
  /// This can be any serializable data, such as JSON or plain text.
  /// </para>
  /// </remarks>
  UPROPERTY(             //
    EditAnywhere,        //
    BlueprintReadWrite,  //
    Category = "Default" //
  )
  FString Response;

public:
  /// <summary>
  /// Gets the unique identifier for this query.
  /// </summary>
  /// <returns>The query id as a 64-bit integer.</returns>
  /// <remarks>
  /// <para>
  /// The query ID is assigned by the CEF framework and is used to match responses to their corresponding requests.
  /// </para>
  /// </remarks>
  UFUNCTION(BlueprintCallable, Category = "Default")
  int64 GetId() const;

  /// <summary>
  /// Gets the content of the query as sent from the browser.
  /// </summary>
  /// <returns>The request content string.</returns>
  /// <remarks>
  /// <para>
  /// This string contains the data or command sent from JavaScript. It is typically a JSON-encoded string or a command
  /// name.
  /// </para>
  /// </remarks>
  UFUNCTION(BlueprintCallable, Category = "Default")
  FString GetRequest() const;

  /// <summary>
  /// Replies to the query with the specified success status, response, and error code.
  /// </summary>
  /// <remarks>
  /// <para>
  /// Call this method after setting <see cref="IsSuccess"/>, <see cref="Response"/>, and <see cref="ErrorCode"/> to
  /// send a response back to the browser. Once replied, the query cannot be replied to again.
  /// </para>
  /// <para>
  /// This method is typically called from Blueprint or C++ after processing the query.
  /// </para>
  /// </remarks>
  UFUNCTION(BlueprintCallable, Category = "Default")
  bool Reply() const;

protected:
  /// <summary>
  ///
  /// </summary>
  /// <returns></returns>
  static UCefViewQuery* CreateInstance(UObject* InOuter, int64 InId, const FString& InRequest);

private:
  /// <summary>
  ///
  /// </summary>
  TWeakObjectPtr<UObject> Host;

  /// The unique identifier for the query, assigned by the CEF framework.
  /// </summary>
  /// <remarks>
  /// Used to correlate requests and responses between the browser and Unreal Engine.
  /// </remarks>
  int64 Id;

  /// <summary>
  /// The content of the query as sent from the browser.
  /// </summary>
  /// <remarks>
  /// Contains the raw data or command string provided by JavaScript.
  /// </remarks>
  FString Request;

  /// <summary>
  /// The lock for the reply operation.
  /// </summary>
  mutable FCriticalSection ReplyLock;

  /// <summary>
  /// Indicates whether the query has been replied to.
  /// </summary>
  /// <remarks>
  /// Used internally to ensure that each query receives only one response.
  /// </remarks>
  mutable bool bHasReplied = false;

  /// <summary>
  /// Exposes members to <see cref="UCefView"/>
  /// </summary>
  friend class UCefView;
};
