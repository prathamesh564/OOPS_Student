"use client";

import Link from "next/link";
import Header from "./components/Header";
import Footer from "./components/Footer";

export default function Home() {
  return (
    <div>
      <Header />

      <div className="text-center mt-10">
        <h1 className="text-3xl font-bold mb-3">Welcome to Student Portal</h1>
        <p className="text-gray-600">Click below to search student details</p>

        <Link href="./Student">
          <button className="mt-6 bg-blue-600 text-white px-6 py-2 rounded">
            Search Student
          </button>
        </Link>
      </div>

      <Footer />
    </div>
  );
}
