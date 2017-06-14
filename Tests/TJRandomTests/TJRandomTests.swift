import XCTest
@testable import TJRandom

class TJRandomTests: XCTestCase {
    func testExample() {
        // This is an example of a functional test case.
        // Use XCTAssert and related functions to verify your tests produce the correct
        // results.
        XCTAssertEqual(TJRandom().text, "Hello, World!")
    }


    static var allTests: [(String, (TJRandomTests) -> () -> Void)] = [
        ("testExample", testExample),
    ]
}
